#pragma once
#include "Console/GameScene.h"
#include "Console/UiText.h"
#include "Transform.h"

//using namespace FC_Console;

class ConsoleDebugScene :
    public FC_Console::GameScene
{

protected:

    // Inherited via GameScene
    void initaliseLevel ( ) override;
    void drawScene ( ) override;
    void updateScene ( ) override;


public:

    void initaliseScene ( int ) override;

    int loadNextScene ( std::shared_ptr<FC_Console::GameScene> & newScene, bool & loadAdditively ) override;

    void SetTransformToMonitor ( const Transform & transform )
    {
        _monitor = &transform;
    }


private:

    FC_Console::UiText _textbox = FC_Console::UiText ( "Camera Position (%06.2f, %06.2f, %06.2f)", 100 ) ;

    const Transform * _monitor = nullptr;

};

