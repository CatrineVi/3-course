#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> 
#include <fstream>
#include <iostream>
#include <cmath>
#include <filesystem>
#include <string.h>
#include <vector>
#include <io.h>
#include <string>
#ifdef _WIN32
#define WINVER 0x0501
#define _WIN32_WINNT WINVER
#include <windows.h>
#include <sys/types.h>
#include <sys\stat.h>
#endif
using namespace std;
namespace fs = std::filesystem;

vector<pair<string, int64_t>> formatCount;

bool checkvec(string str, int64_t size)
{
    for (int i = 0; i < formatCount.size(); i++)
        if (formatCount[i].first == str) {
            formatCount[i].second += size;
            return false;
        }
    return true;
}

void format(LPWSTR file, int64_t size)
{
    wstring ext = file;
    ext = ext.substr(ext.find_last_of(L".") + 1);
    if (ext == L"js" || ext == L"vb") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("js/vb", size));
        else if (checkvec("js/vb", size))
            formatCount.push_back(make_pair("js/vb", size));
    }        
    else if (ext == L"exe") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("exe", size));
        else if (checkvec("exe", size))
            formatCount.push_back(make_pair("exe", size));
    }
    else if (ext == L"txt") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("txt", size));
        else if (checkvec("txt", size))
            formatCount.push_back(make_pair("txt", size));
    }
    else if (ext == L"html" || ext == L"htm" || ext == L"shtm") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("html/htm/shtm", size));
        else if (checkvec("html/htm/shtm", size))
            formatCount.push_back(make_pair("html/htm/shtm", size));
    }
    else if (ext == L"aiff") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("aiff", size));
        else if (checkvec("aiff", size))
            formatCount.push_back(make_pair("aiff", size));
    }
    else if (ext == L"wav") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("wav", size));
        else if (checkvec("wav", size))
            formatCount.push_back(make_pair("wav", size));
    }
    else if (ext == L"mp3") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("mp3", size));
        else if (checkvec("mp3", size))
            formatCount.push_back(make_pair("mp3", size));
    }
    else if (ext == L"mpg" || ext == L"mpeg" || ext == L"mp2") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("mpg/mpeg/mp2", size));
        else if (checkvec("mpg/mpeg/mp2", size))
            formatCount.push_back(make_pair("mpg/mpeg/mp2", size));
    }
    else if (ext == L"bmp") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("bmp", size));
        else if (checkvec("bmp", size))
            formatCount.push_back(make_pair("bmp", size));
    }
    else if (ext == L"avi") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("avi", size));
        else if (checkvec("avi", size))
            formatCount.push_back(make_pair("avi", size));
    }
    else if (ext == L"asf") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("asf", size));
        else if (checkvec("asf", size))
            formatCount.push_back(make_pair("asf", size));
    }
    else if (ext == L"tif") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("tif", size));
        else if (checkvec("tif", size))
            formatCount.push_back(make_pair("tif", size));
    }
    else if (ext == L"gif") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("gif", size));
        else if (checkvec("gif", size))
            formatCount.push_back(make_pair("gif", size));
    }
    else if (ext == L"pct") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("pct", size));
        else if (checkvec("pct", size))
            formatCount.push_back(make_pair("pct", size));
    }
    else if (ext == L"png") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("png", size));
        else if (checkvec("png", size))
            formatCount.push_back(make_pair("png", size));
    }
    else if (ext == L"wma") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("wma", size));
        else if (checkvec("wma", size))
            formatCount.push_back(make_pair("wma", size));
    }
    else if (ext == L"wpl") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("wpl", size));
        else if (checkvec("wpl", size))
            formatCount.push_back(make_pair("wpl", size));
    }
    else if (ext == L"asx") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("asx", size));
        else if (checkvec("asx", size))
            formatCount.push_back(make_pair("asx", size));
    }
    else if (ext == L"m3u") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("m3u", size));
        else if (checkvec("m3u", size))
            formatCount.push_back(make_pair("m3u", size));
    }
    else if (ext == L"wmv") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("wmv", size));
        else if (checkvec("wmv", size))
            formatCount.push_back(make_pair("wmv", size));
    }
    else if (ext == L"jpg" || ext == L"jpeg" || ext == L"jpe"){
        if (formatCount.empty())
            formatCount.push_back(make_pair("jpg/jpeg/jpe", size));
        else if (checkvec("jpg/jpeg/jpe", size))
            formatCount.push_back(make_pair("jpg/jpeg/jpe", size));
    }
    else if (ext == L"jp2") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("jp2", size));
        else if (checkvec("jp2", size))
            formatCount.push_back(make_pair("jp2", size));
    }
    else if (ext == L"jpx" || ext == L"jpf"){
        if (formatCount.empty())
            formatCount.push_back(make_pair("jpx/jpf", size));
        else if (checkvec("jpx/jpf", size))
            formatCount.push_back(make_pair("jpx/jpf", size));
    }
    else if (ext == L"pdf") {
        if (formatCount.empty())
            formatCount.push_back(make_pair("pdf", size));
        else if (checkvec("pdf", size))
            formatCount.push_back(make_pair("pdf", size));
    }
}

int main()
{

    WIN32_FIND_DATAW wfd; //deskriptor

    HANDLE const hFind = FindFirstFileW(L"C:\\NewFolder\\*", &wfd);


    if (INVALID_HANDLE_VALUE != hFind)
    {
        do
        {
            wcout << &wfd.cFileName[0] << endl;
            std::error_code ec{};
            string path = "C:\\NewFolder\\";
            wstring s(& wfd.cFileName[0]);
            string str(s.begin(), s.end());
            path += str;
            cout << path << endl;
            int64_t _file_size = std::filesystem::file_size(path, ec);
            cout << _file_size << endl;
            format(&wfd.cFileName[0], _file_size);
        } while (NULL != FindNextFileW(hFind, &wfd));

        FindClose(hFind);
    }
    cout << endl;
    for (int i = 0; i < formatCount.size(); i++)
        cout << formatCount[i].first << ": " << formatCount[i].second << endl;

    return 0;
}