#include "ConsoleDebugScene.h"

int ConsoleDebugScene::loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively )
{
    loadAdditively = false;
    newScene = nullptr;
    return 0;
}

void ConsoleDebugScene::initaliseLevel ( )
{ 
    _positionTextbox.setGridPosition ( 4, 3 );
    _positionTextbox.setActive ( true );
 
    _rotationTextbox.setGridPosition ( 4, 4 );
    _rotationTextbox.setActive ( true );
}

void ConsoleDebugScene::drawScene ( )
{
    drawGameObject ( _positionTextbox );
    drawGameObject ( _rotationTextbox );
}

void ConsoleDebugScene::updateScene ( )
{ 

    if ( _monitor != nullptr )
    {
        const glm::vec3 & position = _monitor->GetPosition ( );
        const glm::vec3 & rotation = _monitor->GetRotation ( );
        _positionTextbox.updateText ( position.x, position.y, position.z );
        _rotationTextbox.updateText ( rotation.x, rotation.y, rotation.z );
    }

}

void ConsoleDebugScene::initaliseScene ( int lastSceneReturnCode )
{ 
    GameScene::initaliseScene ( lastSceneReturnCode );
    initaliseLevel ( );
}
