#include "Game/Game.h"

namespace library
{
    /*--------------------------------------------------------------------
      Function definitions
    --------------------------------------------------------------------*/
    void PrintHi()
    {
      OutputDebugString(L"hhhhi\n");
      MessageBox(nullptr, L"hi", L"Game Graphics Programming", MB_OK);
    }
}