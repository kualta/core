/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_CAMERALIST_H
#define CORE_CAMERALIST_H

#include "Essentials.h"
#include "Singleton.h"
#include "Components/Camera.h"

namespace core {

class CameraList : public Singleton<CameraList> {
public:

    SceneCamera* GetSceneViewCamera();
    Camera* GetGameViewCamera();

protected:
    friend class SceneModule; // < Construction only allowed from SceneModule
    friend class Camera;      // < Registration only allowed from Camera

    CameraList();

    /** Add camera to Camera List */
    void Register(Camera* camera);

    /** Remove camera from Camera List */
    void Unregister(Camera* camera);

    std::vector<Camera*> cameras { };

};

}

#endif //CORE_CAMERALIST_H
