#include "game.h"
#include "filenames.h"
#include <cmath>
#include "global.h"

using namespace std;

Game::Game()
{
    window = NULL;
	gameover = false;
	abilities = Abilities::getInstance();
    pauseMenu = new Menu();
    cursor = new Cursor();
    startMenu = new StartMenu();
	animationMgr = AnimationMgr::getInstance();
	wasFired = false;
	button = new InGameButton( Point( 2165.0, 186.0 ), "door" );
	enemies.push_back(new Turtle);
	actionbar = new ActionBar();
}

Game::~Game()
{
    if(window)
        delete window;
    animationMgr->release();
}

void Game::init()
{
    //Mouse BOOL
    showMouseCoords = true;

    window = Window::getInstance();

    if(window)
    {
		gameover = false;
    }
    else
    {
        gameover = true;
        return;
    }

    //Initiliaze the input system.
    input = Input::getInstance();

    //Get our resourceMgr
    resourceMgr = ResourceMgr::getInstance();
    startMenu->init();
    pauseMenu->init();

    snotch = Snotch::getInstance();
    //snotch->setPos( -300, 800 );
    snotch->setPos( 3500, 800);
    enemies[0]->setPosition( Point(4900, 800));

    for(int i = 0; i < enemies.size(); ++i)
        enemies[i]->init();

    abilities->init();

    addObject("BOX" , 50, 50, 20, Point(2060,580));
    addObject("BOX" , 85, 85, 12, Point(1050, 300));
    addObject("health" , 50, 40, 10, Point(4400, 300));
    addObject("barrel" , 50, 80, 10, Point(-200, 1000));
    addObject("barrel" , 50, 80, 10, Point(-200, 900));
    addObject("barrel" , 50, 80, 10, Point(-200, 800));
    addObject("barrel" , 50, 80, 10, Point(4250, 300));

    currentLevel.loadObjects( TEST_OBJECTS_FILE );
    currentLevel.insert(objects[0]);
    currentLevel.insert(objects[1]);
    currentLevel.insert(barrels[0]);
    currentLevel.insert(barrels[1]);
    currentLevel.insert(barrels[2]);
    currentLevel.insert(snotch);

    cursor = new Cursor();
    cursor->init();

    window->showCursor( false );
    actionbar->init();

    snotch->init();

    resourceMgr->loadFont( "./data/fonts/arial.ttf", "ARIAL", 24 );
    resourceMgr->loadFont( "./data/fonts/monaco.ttf", "MONACO", 12 );
    resourceMgr->loadImage( FILE_HEALTH_BAR , "healthBar" );
    resourceMgr->loadImage( FILE_HEALTH_BAR_BW , "healthBarBw" );
    resourceMgr->loadImage( FILE_LIFE_BAR , "life" );
    resourceMgr->loadImage( FILE_ARROW , "arrow" );
    resourceMgr->loadImage( FILE_EKIS , "ekis" );
    resourceMgr->loadImage( FILE_CRATE, "crate" );
    resourceMgr->loadImage( FILE_BK1, "bk1" );
    resourceMgr->loadImage( FILE_FIRST_AID, "health" );
    resourceMgr->loadImage( FILE_BARREL, "barrel" );
    resourceMgr->loadImage( FILE_EXPLOSION, "explosion" );
    resourceMgr->loadImage( FILE_CLOUD, "cloud");
	resourceMgr->loadImage( FILE_TREE, "tree" );
	resourceMgr->loadImage( FILE_MOON, "moon" );
	resourceMgr->loadImage( FILE_FENCE, "fence" );
	resourceMgr->loadImage( FILE_FOG, "fog" );
	resourceMgr->loadImage( FILE_STARS, "stars");

//string bgAlias, double speed, unsigned int layer, double width, double height, Point ul, bool xRepeat

    bg.load( FILE_BG_NIGHTTIME );

}

void Game::addObject(string type, int width, int height, int mass, Point ul)
{
    if(type == "barrel")
    {
        barrels.push_back(new Barrel(ul,width,height,mass));
        barrels[barrels.size()-1]->init();
    }
    else
    {
        objects.push_back(new Object(type, ul,width,height,mass));
        objects[objects.size()-1]->init();
    }
}

void Game::blowBarrel()
{
    for(int i =0; i < barrels.size(); i++)
    {
        if(barrels[i]->isBlown())
        {

            if(barrels[i]->timePassed() > 100)
            {
                for(int j = 0; j < objects.size(); j++)
                    barrels[i]->radialForce(objects[j], 400,10000);

                for(int j = 0; j < enemies.size(); j++)
                {
                    barrels[i]->radialForce(enemies[j],400,10000);
                }
                for(int j = 0; j < barrels.size(); j++)
                {
                    if(!barrels[j]->isBlown())
                    {
                        barrels[i]->radialForce(barrels[j],400,10000);
                        barrels[j]->hit(15);
                    }
                }
                barrels[i]->radialForce(snotch,400,50000);
                barrels.erase(barrels.begin()+i);
                i--;
            }
        }
    }
}

void Game::checkInput()
{
    startMenu->checkInput();

    if( !startMenu->isGameStart() && !startMenu->isMenuOpen() )
    {
        pauseMenu->checkInput();
        if ( input->getKeyInput() == "r" )
        {
            currentLevel.clear();
            currentLevel.loadObjects( TEST_OBJECTS_FILE );
        }

        //Testing healthbar
        if( input->getKeyInput() == "l" )
        {
            healthBar.lock();
            livesBar.lock();
        }

        if( input->getKeyInput() == "u" )
        {
            healthBar.unLock();
            livesBar.unLock();
        }
        actionbar->checkInput();
    }
}

void Game::calcFrameRate()
{
    fpsTime += window->timeSinceLastFrame();
    if(fpsTime >= 1.0)
    {
        char buffer[50];
        sprintf(buffer, "Snotch    FPS: %u", window->getFrameRate());
        SDL_WM_SetCaption(buffer, buffer);
        fpsTime = 0;
    }
}

void Game::checkAbilitiesOnAllEntities()
{
    //See if any of the abilities hit the enemies
    for(int i = 0; i < enemies.size();i++)
    {
        abilities->checkHit(enemies[i]);

        //Once we check the powers, check the health
        //of the enemies to see if they lost all of
        //their health.
        if( enemies[i]->health <= 0)
        {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
    //See if any of the abilities hit the enemies or player.
    for(int i = 0; i < objects.size();i++)
    {
        abilities->checkHit(objects[i]);
    }

    //Check the powers against the barrels.
    for(int i = 0; i < barrels.size(); i ++)
    {
        for(int j = 0; j < abilities->power.size();j++)
        {
            if(abilities->power[j]->didIntersect(barrels[i]))
            {
                if(abilities->power[j]->getType() == "push")
                    barrels[i]->transferEnergy(10000, abilities->power[j]->getAngle());
                if(abilities->power[j]->getType() == "fireball")
                {
                    barrels[i]->transferEnergy(5000,abilities->power[j]->getAngle());
                    barrels[i]->hit(25);
                }
                delete abilities->power[j];
                abilities->power.erase(abilities->power.begin()+j);
                j-=1;
            }
        }
    }
}

void Game::updateEnemies()
{
    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->runAI();

        if(snotch->didIntersect(enemies[i]))
            snotch->setHealth(snotch->getHealth() - 10.0);
    }
}

void Game::checkTriggers()
{
    if( snotch->didIntersect( button ) || objects[0]->didIntersect(button))
        button->press();
    else
        button->unPress();
}

void Game::updateGameObjects()
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->update();

        if(objects[i]->getType() == "health")
        {
            if(snotch->didIntersect(objects[i]) && snotch->getHealth() != 100.0)
            {
                snotch->setHealth(snotch->getHealth() + 10.0);
                objects.erase(objects.begin() + i);
            }
        }
    }

    for(int i = 0; i < barrels.size(); i++)
       barrels[i]->update();
    blowBarrel();
}

void Game::updateUI()
{
    healthBar.update();
    livesBar.update();
    actionbar->update();
}

void Game::levelDetectionChecks()
{
    //Check level on Snotch.
    currentLevel.didDetect(snotch);

    //Check level on enemies.
    for(int i = 0; i < enemies.size(); i++)
        currentLevel.didDetect(enemies[i]);

    //Check level on objects.
    for(int i=0; i < objects.size(); i++)
        currentLevel.didDetect(objects[i]);

    //Check level on barrels.
    for(int i =0; i < barrels.size(); i++)
        currentLevel.didDetect(barrels[i]);
}

void Game::updateCoordinateSystem()
{
    //How to center the coordinate system about a point.
    //EVERYONE THIS NEEDS TO BE LAST, DO NOT PUT STUFF UNDER THIS.
    window->setCoord(snotch->getPos().getX() - (window->rightCoord() - window->leftCoord())   / 2.0,
                     snotch->getPos().getX() + (window->rightCoord() - window->leftCoord())   / 2.0,
                     snotch->getPos().getY() - (window->topCoord()   - window->bottomCoord() - 400 ) / 2.0,
                     snotch->getPos().getY() + (window->topCoord()   - window->bottomCoord() + 400 ) / 2.0);
}

void Game::drawLevel()
{
    bg.draw();
    currentLevel.draw();
}

void Game::drawUI()
{
    healthBar.draw(snotch->getHealth());
    livesBar.draw(snotch->getLives());
    actionbar->draw();
}

void Game::drawGameObjects()
{
    for(int i = 0; i < objects.size(); i++)
        objects[i]->draw();

    for(int i =0; i < barrels.size(); i++)
        barrels[i]->draw();
}

void Game::drawEnemies()
{
    glColor3f(1.0,1.0,1.0);

    for(int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->draw();
    }
}

void Game::handleLogic()
{
    calcFrameRate();
    checkInput();
    startMenu->update();

    if(!startMenu->isGameStart() && !startMenu->isMenuOpen())
    {
        pauseMenu->update();
        cursor->setShown(true);

        if(!pauseMenu->isMenuOpen())
        {
            //If we are not on the menu, hide the cursor.
            cursor->setShown(false);

            //Move all background layers that move by themselves.
        	bg.update();

            //Move all of the abilities.
            abilities->update();

            //Update Snotch.
            snotch->update();

            //Run all the enemy AI and move them.
            updateEnemies();

            //Move and update all the objects in the game.
            updateGameObjects();

            //Check to see if the triggers are triggered or not
            //if so, handle the trigger events that correspond to
            //the triggers.
            checkTriggers();

            //Checks to see if the abilities hit anything in
            //the game. If so, affect what it hit accordingly.
            checkAbilitiesOnAllEntities();

            //Check all the entities in the game against the level blocks.
            //Correct any object's placement and speed if they intersected
            //with the level blocks.
            levelDetectionChecks();

            //Update everything on the UI.
            updateUI();

            //This should be last, centers the coordinate system on the player.
            updateCoordinateSystem();
        }
    }
}



void Game::renderGame()
{
    // Draw the level objects
    // you can now simply add objects to the
    // text file and they will be drawn

    startMenu->draw();

    if(!startMenu->isGameStart() && !startMenu->isMenuOpen())
    {
        drawLevel();

        drawEnemies();

        abilities->draw();

        button->draw();
        snotch->draw();

        drawGameObjects();

        drawUI();
        pauseMenu->draw();
    }

    if(cursor->isShown())
        cursor->draw();
}

void Game::play()
{
    //Game Loop
    while(!gameover)
	{
	    //Tell the window to record the starting time of the new frame.
        window->startFrame();

        //Clear the screen so we can begin the next frame.
        glClearColor(0.0, 0.0, 0.1, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Handle all input and window events.
        //If a quit signal was received from the window, we
        //quit the program.
        if(input->handleEvents() == QUIT_SIGNAL_RECEIVED)
            gameover = true;

        //Handles all the movement, AI, calculations, etc.
        handleLogic();

        //Draws everything in the scene.
    	renderGame();

        //Swap the new buffer to output everything that was drawn to the screen.
		SDL_GL_SwapBuffers();

        //Tell the window to record the stop time of the current frame.
        window->endFrame();
		//Reset the buffered input to nothing.
		input->resetInput();
	}

    //Free the resources
	resourceMgr->stopMusic();
	resourceMgr->release();
	snotch->release();
	abilities->release();
}


