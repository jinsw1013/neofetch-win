#pragma once


#include <xstring>

// the reason that these constants are defined in a header is so that you can easily customize them!

const std::wstring win10art[20] = {
    L"                                ..,",
    L"                    ....,,:;+ccllll",
    L"      ...,,+:;  cllllllllllllllllll",
    L",cclllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"                                   ",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"llllllllllllll  lllllllllllllllllll",
    L"`'ccllllllllll  lllllllllllllllllll",
    LR"(      `' \\*::  :ccllllllllllllllll)", // <---- this line had to be a raw string literal because of the backslashes
    L"                       ````''*::cll",         // which the compiler assumes are escape chars (like \n), but if you're
    L"                                 ``"          // customizing the art feel free to change that
    };


//                                ..,
//                    ....,,:;+ccllll
//      ...,,+:;  cllllllllllllllllll
//,cclllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//                                   
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//llllllllllllll  lllllllllllllllllll
//`'ccllllllllll  lllllllllllllllllll
//      `' \\*::  :ccllllllllllllllll
//                       ````''*::cll
//                                 ``


const std::wstring win11art[19] = {
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"                                   ",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    };

//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll
//llllllllllllllll   llllllllllllllll

// identical to win11art but you could customize this if you so choose

const std::wstring unknownart[19] = {
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"                                   ",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    L"llllllllllllllll   llllllllllllllll",
    };