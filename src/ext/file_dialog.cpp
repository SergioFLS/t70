// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#include "file_dialog.h"

#include <SDL.h>

#if defined(__WINRT__)

#include <ppltasks.h>
#include <Robuffer.h>
#include <wrl/client.h>
#include <collection.h>

using namespace Platform;
using namespace Concurrency;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::Pickers;
using namespace Microsoft::WRL;

#define UTF8ToString(S) (wchar_t *)SDL_iconv_string("UTF-16LE", "UTF-8", (char *)(S), SDL_strlen(S)+1)
#define StringToUTF8(S) SDL_iconv_string("UTF-8", "UTF-16LE", (char *)(S), (SDL_wcslen(S)+1)*sizeof(wchar_t))

byte* GetPointerToData(IBuffer^ buffer)
{
	Object^ obj = buffer;
	ComPtr<IInspectable> insp(reinterpret_cast<IInspectable*>(obj));
	ComPtr<IBufferByteAccess> bufferByteAccess;
	insp.As(&bufferByteAccess);
	byte* data = nullptr;
	bufferByteAccess->Buffer(&data);

	return data;
}

IBuffer^ IBufferFromArray(Array<unsigned char>^ data)
{
	DataWriter^ dataWriter = ref new DataWriter();
	dataWriter->WriteBytes(data);
	return dataWriter->DetachBuffer();
}

IBuffer^ IBufferFromPointer(LPBYTE pbData, DWORD cbData)
{
	auto byteArray = new ArrayReference<unsigned char>(pbData, cbData);
	return IBufferFromArray(reinterpret_cast<Array<unsigned char>^>(byteArray));
}

void file_dialog_load(file_dialog_load_callback callback, void* data)
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();

	openPicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	openPicker->FileTypeFilter->Append("*");

	create_task(openPicker->PickSingleFileAsync()).then([callback, data](StorageFile^ file)
	{
		if (file)
		{
			create_task(file->OpenAsync(FileAccessMode::Read)).then([callback, data, file](IRandomAccessStream^ stream)
			{
				Buffer^ buffer = ref new Buffer((int)stream->Size);

				create_task(stream->ReadAsync(buffer, buffer->Capacity, InputStreamOptions::Partial)).then([callback, data, file](IBuffer^ buffer)
				{
					auto ptr = GetPointerToData(buffer);
					auto size = buffer->Length;

					std::wstring fooW(file->Name->Begin());
					callback(StringToUTF8(fooW.c_str()), ptr, size, data, 0);
				});
			});

		}
		else
		{
			callback(NULL, NULL, 0, data, 0);
		}
	});
}

void file_dialog_save(file_dialog_save_callback callback, const char* name, const u8* buffer, size_t size, void* data, u32 mode)
{
	FileSavePicker^ savePicker = ref new FileSavePicker();

	savePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	savePicker->SuggestedFileName = ref new Platform::String(UTF8ToString(name));

	auto allExtensions = ref new Platform::Collections::Vector<String^>();
	allExtensions->Append(".tic");
	allExtensions->Append(".html");
	allExtensions->Append(".gif");

	savePicker->FileTypeChoices->Insert("TIC files", allExtensions);

	create_task(savePicker->PickSaveFileAsync()).then([callback, data, buffer, size](StorageFile^ file)
	{
		if (file)
		{
			create_task(file->OpenAsync(FileAccessMode::ReadWrite)).then([callback, data, file, buffer, size](IRandomAccessStream^ stream)
			{
				auto ibuffer = IBufferFromPointer(const_cast<u8*>(buffer), (DWORD)size);

				if (ibuffer)
				{
					create_task(FileIO::WriteBufferAsync(file, ibuffer)).then([callback, data, file]()
					{
						callback(true, data);
					});
				}
				else callback(false, data);
			});
		}
		else callback(false, data);

	});
}

const char* folder_dialog(void* data)
{
	return NULL;
}

#endif
