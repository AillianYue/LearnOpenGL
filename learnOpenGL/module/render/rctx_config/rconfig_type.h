#pragma once
#include <string>

namespace learnOpenGL {
namespace config {


struct ViewSize {
    int x;
    int y;
    int w;
    int h;
};

struct WinParam {
    ViewSize WinSize;
    ViewSize AreaLeft;
    ViewSize AreaRight;
};

struct ParamRenderDemo
{
    std::string demoText;
};

struct AdjustParam {
    WinParam paramWin;
    ParamRenderDemo paramRenderDemo;
};



}
}