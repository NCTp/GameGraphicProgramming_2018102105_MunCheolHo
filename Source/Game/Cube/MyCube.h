﻿/*+===================================================================
  File:      YOURCUBE.H

  Summary:  Child Cube header file contains declarations of
             YourCube class used for the lab samples of Game
             Graphics Programming course.

  Classes: Renderable

  � 2022 Kyung Hee University
===================================================================+*/
#pragma once

#include "Common.h"

#include "Cube/BaseCube.h"


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
      Class:    YourCube

      Summary:  YourCube class

      Methods:  Update
                  Update the cube each frame
                YourCube
                  Constructor.
                ~YourCube
                  Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class MyCube : public BaseCube
{
public:
    MyCube() = default;
    MyCube(const MyCube& other) = delete;
    MyCube(MyCube&& other) = delete;
    MyCube& operator=(const MyCube& other) = delete;
    MyCube& operator=(MyCube&& other) = delete;
    ~MyCube() = default;

    virtual void Update(_In_ FLOAT deltaTime) override;
};