#pragma once
#include "Console/GameScene.h"
#include "Console/UiText.h"
#include "Transform.h"

using namespace FC_Console;

class ConsoleDebugScene :
    public GameScene
{

protected:

    // Inherited via GameScene
    void initaliseLevel ( ) override;
    void drawScene ( ) override;
    void updateScene ( ) override;


public:

    void initaliseScene ( int ) override;

    int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) override;

    void SetTransformToMonitor ( const Transform & transform )
    {
        _monitor = &transform;
    }


private:

    UiText _textbox = UiText ( "Camera Position (%06.2f, %06.2f, %06.2f)", 100 ) ;

    const Transform * _monitor = nullptr;

};

