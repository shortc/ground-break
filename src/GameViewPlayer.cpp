
#include "GameViewPlayer.h"

using namespace std;

GameViewPlayer::GameViewPlayer (GameLogic* game, shared_ptr<sf::RenderWindow> &window_ptr)
{
    if( !fireBg.loadFromFile( "../Assets/Images/bg_fire.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load fire background " << endl;
    }
    if( !waterBg.loadFromFile( "../Assets/Images/bg_water.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load water background " << endl;
    }
    if( !earthBg.loadFromFile( "../Assets/Images/bg_earth.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load earth background " << endl;
    }
    if( !airBg.loadFromFile( "../Assets/Images/bg_air.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load air background " << endl;
    }
    if( !elementalText.loadFromFile( "../Assets/Images/items.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load items.png " << endl;
    }
    if( !UIText.loadFromFile( "../Assets/Images/spellBar.png" ) )
    {
        hasTextureLoaded = false;
        cout << "Cannot load items.png " << endl;
    }
    if(hasTextureLoaded)
    {
        fireBg.setRepeated(true);
        waterBg.setRepeated(true);
        earthBg.setRepeated(true);
        airBg.setRepeated(true);
        elementalIcon.setRadius(spellIconSize);
        elementalIcon.setPointCount(60);
        elementalIcon.setTextureRect(sf::IntRect(itemTextureSize*game->getStartingElement(),0*spellTextNum,itemTextureSize,itemTextureSize));
        elementalIcon.setTexture(&elementalText);
        elementalIcon.setPosition(bckgW/2 + 72  ,bckgH/2 + (screenH - 24 ));
        UIIcon.setSize(sf::Vector2f(192,32));
        UIIcon.setPosition(bckgW/2 + 64  ,bckgH/2 + (screenH - 32 ));
        UIIcon.setTextureRect(sf::IntRect(0,0,384,64));
        UIText.setRepeated(true);
        UIIcon.setTexture(&UIText);
        itemIcon.setRadius(spellIconSize);
        itemIcon.setPointCount(60);
        itemIcon.setTextureRect(sf::IntRect(itemTextureSize*1,1*spellTextNum,itemTextureSize,itemTextureSize));
        itemIcon.setTexture(&elementalText);
        itemIcon.setPosition(bckgW/2 + 72 + 64  ,bckgH/2 + (screenH - 24 ));
        cout<< "SUCESS"<<endl;
    }
    this -> game = game;
    this -> window_ptr = window_ptr;

    this -> bckgTextNum = game -> getStartingElement();
    this -> spellTextNum = game -> getStartingElement();
    this -> spellTextCdNum = game -> getStartingElement();

}





bool GameViewPlayer::checkKeyEvents( float deltaTime , sf::Keyboard::Key keycode)
{

        if( game -> getGameState() == 0 )
        {
            inputTimer += deltaTime;
            if(inputTimer>50)
            {
                inputTimer = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    menu -> setSelected(-1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    menu -> setSelected(1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {

                    if( menu -> getSelected() == 0 )
                    {
                        game -> setGameState(1);
                    }
                    if( menu -> getSelected() == 1 )
		    {
                        game -> setGameState(3);
		    }
                }
            }


        }

        if( game -> getGameState() == 1 )
        {
            inputTimer += deltaTime;
            if(inputTimer > 100)
            {
                inputTimer = 0;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    menu -> setSelectedElement(-1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    menu -> setSelectedElement(1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    background.setSize(sf::Vector2f(bckgW,bckgH));
                    playerView.reset(sf::FloatRect(bckgW/2,bckgH/2,screenW,screenH));
                    background.setTextureRect(sf::IntRect(textureSize,textureSize,bckgW,bckgH));
                    setBackgroundTexture(menu -> getSelectedElement());
                    window_ptr -> setView(playerView);
                    menu -> stopMusic();
                    game -> setGameState(2);
                    game -> setStartingElement(menu -> getSelectedElement());
                    game -> initiliaze(bckgW, bckgH, screenW, screenH, textureSize, playerW, playerH);
                    game -> resetPlayer();


                }
            }
        }

        if( game -> getGameState() == 3 )
        {
		inputTimer += deltaTime;
		if(inputTimer > 100 && !wait)
		{
			inputTimer = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				menu -> setSelectedKeybind(-1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				menu -> setSelectedKeybind(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				menu -> choosingKeybind();
				wait = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game -> setGameState(0);
			}
		}
		else if(wait){
			inputTimer = 0;
		    	if(keycode != sf::Keyboard::Unknown){
				menu -> newKeybind(keycode);
				wait = false;
			}
		}
	}

        if( game -> getGameState() == 2 )
        {
            movingX = false;
            movingY = false;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    movingY = true;
                    game -> setDirection(Player::NORTH,deltaTime);

                    sf::Vector2f vect(game -> getPlayerCoord());

                    if ((vect.y + playerH/2) < ((bckgH - screenH/2) - playerH) && ((vect.y + playerH/2) > (screenH/2 + playerH)))
                    {
                        playerView.move(0, -camMoveSpeed *deltaTime);
                        window_ptr -> setView(playerView);
                        UIIcon.move(0, -camMoveSpeed *deltaTime);
                        elementalIcon.move(0, -camMoveSpeed *deltaTime);
                        itemIcon.move(0, -camMoveSpeed *deltaTime);
                    }


                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    movingY = true;
                    sf::Vector2f vect(game -> getPlayerCoord());
                    game -> setDirection(Player::SOUTH,deltaTime);

                    if ((vect.y + playerH/2) < ((bckgH - screenH/2) - playerH) && ((vect.y + playerH/2) > (screenH/2 + playerH)))
                    {
                        playerView.move(0, camMoveSpeed *deltaTime);
                        window_ptr -> setView(playerView);
                        UIIcon.move(0, camMoveSpeed *deltaTime);
                        elementalIcon.move(0, camMoveSpeed *deltaTime);
                        itemIcon.move(0, camMoveSpeed *deltaTime);
                    }

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    movingX = true;
                    sf::Vector2f vect(game -> getPlayerCoord());
                    game -> setDirection(Player::EAST,deltaTime);

                    if ((vect.x + playerW/2) < ((bckgW - screenW/2) - playerW) && ((vect.x + playerW/2) > (screenW/2 + playerW)))
                    {
                        playerView.move( camMoveSpeed * deltaTime,0 );
                        window_ptr -> setView(playerView);
                        UIIcon.move( camMoveSpeed * deltaTime,0 );
                        elementalIcon.move( camMoveSpeed * deltaTime,0 );
                        itemIcon.move( camMoveSpeed * deltaTime,0 );
                    }


                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    movingX = true;
                    sf::Vector2f vect(game -> getPlayerCoord());
                    game -> setDirection(Player::WEST,deltaTime);
                    if ((vect.x + playerW/2) < ((bckgW - screenW/2) - playerW) && ((vect.x + playerW/2) > (screenW/2 + playerW)))
                    {
                        playerView.move( -camMoveSpeed * deltaTime ,0 );
                        window_ptr -> setView(playerView);
                        UIIcon.move( -camMoveSpeed * deltaTime ,0 );
                        elementalIcon.move( -camMoveSpeed * deltaTime ,0 );
                        itemIcon.move( -camMoveSpeed * deltaTime ,0 );
                    }
                }
                //Pick up item
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    game -> grabItem();
                    int itemDisplay = game->player.currentItem();
                    if( itemDisplay > 0 )
                    {
                        itemIcon.setTextureRect(sf::IntRect(itemTextureSize*itemDisplay,itemTextureSize*1,itemTextureSize,itemTextureSize));
                    }

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
                {
                    game -> createRangedEnemy(deltaTime);
                }


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    game -> createPlayerAttack('N',deltaTime);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    game -> createPlayerAttack('S',deltaTime);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    game -> createPlayerAttack('W',deltaTime);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    game -> createPlayerAttack('E',deltaTime);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    game -> setGameState(0);
                    elementalIcon.setPosition(bckgW/2 + 72  ,bckgH/2 + (screenH - 24 ));
                    itemIcon.setPosition(bckgW/2 + 72 + 64   ,bckgH/2 + (screenH - 24 ));
                    UIIcon.setPosition(bckgW/2 + 64  ,bckgH/2 + (screenH - 32 ));
                    playerView.reset(sf::FloatRect(0,0,screenW,screenH));
                    window_ptr -> setView(playerView);
                    game -> clearGame();
                }


            if(movingX == false && movingY == false)
            {
                game -> idle();
            }

        }
    return wait;
}





void GameViewPlayer::setTitleScreen(TitleScreen* screen)
{
    menu = screen;
}

void GameViewPlayer::update(float deltaTime)
{
    if(game -> isBasicAttackOnCd())
    {
        elementalIcon.setTextureRect(sf::IntRect(itemTextureSize*0,itemTextureSize*1,itemTextureSize,itemTextureSize));
    }
    else
    {
        elementalIcon.setTextureRect(sf::IntRect(itemTextureSize*game->getStartingElement(),0*spellTextNum,itemTextureSize,itemTextureSize));
    }
    window_ptr -> draw( game -> getPlayer());
    window_ptr -> draw(UIIcon);
    window_ptr -> draw(elementalIcon);

    if(game ->player.currentItem() > 0 )
    {
           window_ptr -> draw(itemIcon);
    }

}
void GameViewPlayer::drawBg()
{
    window_ptr -> draw(background);
}
void GameViewPlayer::setBackgroundTexture(int element)
{
    cout<<"ELEMENT"<<element<<endl;
    switch(element)
    {
    case 0:
        background.setTexture(&fireBg);
        break;
    case 1:
        background.setTexture(&waterBg);
        break;
    case 2:
        background.setTexture(&earthBg);
        break;
    case 3:
        background.setTexture(&airBg);
        break;
    }
}
