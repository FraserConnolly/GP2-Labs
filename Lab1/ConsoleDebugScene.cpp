#include "ConsoleDebugScene.h"

int ConsoleDebugScene::loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively )
{
    loadAdditively = false;
    newScene = nullptr;
    return 0;
}

void ConsoleDebugScene::initaliseLevel ( )
{ 
    _textbox.setGridPosition ( 10, 10 );
    _textbox.setActive ( true );
}

void ConsoleDebugScene::drawScene ( )
{
    drawGameObject ( _textbox );
}

void ConsoleDebugScene::updateScene ( )
{ 

    if ( _monitor != nullptr )
    {
        const glm::vec3 & position = _monitor->GetPosition ( );
        _textbox.updateText ( position.x, position.y, position.z );
    }

}

void ConsoleDebugScene::initaliseScene ( int lastSceneReturnCode )
{ 
    GameScene::initaliseScene ( lastSceneReturnCode );
    initaliseLevel ( );
}
