/*****************************************************************************************
* Desc: Tutorial 02 IND_Surface
*****************************************************************************************/

#include "common\include\CIndieLib.h"
#include "common\include\IND_Surface.h"
#include "common\include\IND_Entity2d.h"
#include "common\include\IND_Animation.h"
#include <vector>
using namespace std;

/*
==================
Main
==================
*/
int IndieLib()
{
	
	// ----- IndieLib intialization -----

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	
	// ----- Surface loading -----

	// nov animiran bg
	IND_Animation  *newBG = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(newBG, "../SpaceGame/animation/bganimation.xml", IND_OPAQUE, IND_32)) return 0;


	// Loading sprite of a star
	IND_Surface *mSurfaceHeart= IND_Surface::newSurface();
	if (!mI->_surfaceManager->add(mSurfaceHeart, "../SpaceGame/newresources/heart.png", IND_ALPHA, IND_32)) return 0;

	// ----- Animations loading -----

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter1 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter1, "../SpaceGame/resources/animations/character1.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Characters animations, we apply a color key of (0, 48, 152)
	IND_Animation *mAnimationCharacter2 = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationCharacter2, "../SpaceGame/resources/animations/character2.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;

	// Dust animation, we apply a color key of (255, 0, 255)
	IND_Animation *mAnimationDust = IND_Animation::newAnimation();
	if (!mI->_animationManager->addToSurface(mAnimationDust, "../SpaceGame/resources/animations/dust.xml", IND_ALPHA, IND_16, 255, 0, 255)) return 0;

	// ----- Set the surface and animations into 2d entities -----
	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mBack);					// Entity adding
	mBack->setAnimation(newBG);

	//surce
	//pylnim vector s 3 entity2d obekta, inicializirame gi chreze IND_Entity2d::newEntity2d(), pylnim gi v scenata prez entity2dManager-a i im postavqme textura s setSurface
	vector<IND_Entity2d*> healthbar;
	IND_Entity2d *a,*b,*c;
	healthbar.push_back(a);
	healthbar.push_back(b);
	healthbar.push_back(c);
	healthbar[0] = IND_Entity2d::newEntity2d();
	healthbar[1] = IND_Entity2d::newEntity2d();
	healthbar[2] = IND_Entity2d::newEntity2d();
	
	mI->_entity2dManager->add(healthbar[0]);
	mI->_entity2dManager->add(healthbar[1]);
	mI->_entity2dManager->add(healthbar[2]);
	healthbar[0]->setSurface(mSurfaceHeart);
	healthbar[1]->setSurface(mSurfaceHeart);
	healthbar[2]->setSurface(mSurfaceHeart);

	// Character 1
	IND_Entity2d *mPlayer1 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer1);					// Entity adding
	mPlayer1->setAnimation(mAnimationCharacter1);				// Set the animation into the entity

	// Character 2
	IND_Entity2d *mPlayer2 = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mPlayer2);					// Entity adding
	mPlayer2->setAnimation(mAnimationCharacter2);				// Set the animation into the entity

	// Dust explosion
	IND_Entity2d *mDust = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mDust);					// Entity adding
	mDust->setAnimation(mAnimationDust);					// Set the animation into the entity

	// ----- Changing the attributes of the 2d entities -----
	healthbar[0]->setScale(0.3F, 0.3F);
	healthbar[1]->setScale(0.3F, 0.3F);
	healthbar[2]->setScale(0.3F, 0.3F);
	// Player 1
	mPlayer1->setSequence(0);						// Choose sequence
	mPlayer1->setPosition(140, 200, 0);
	mPlayer1->setNumReplays(0);
	mPlayer1->getAnimation()->setIsActive(0, false);
	mPlayer1->setMirrorX(1);


	// Dust explosion
	mDust->setPosition(360, 250, 0);
	mDust->setNumReplays(0);

	// Player 2
	mPlayer2->setSequence(0);						// Choose sequence
	mPlayer2->setPosition(550, 200, 0);
	mPlayer2->setNumReplays(-1);						// The animation will be displayed 3 times


	//star
	float width = mSurfaceHeart->getWidth()*0.3F;
	healthbar[0]->setPosition(mI->_window->getWidth() - width, 0, 100);
	healthbar[1]->setPosition(mI->_window->getWidth() - 2.1F*width, 0, 100);
	healthbar[2]->setPosition(mI->_window->getWidth() - 3.2F*width, 0, 100);
	// ----- Main Loop -----
	int counter = 2;
	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		
		mI->_input->update();
		if (mI->_input->onKeyPress(IND_SPACE) && mPlayer1->getAnimation()->getActualFramePos(0)==9)
		{
			mDust->setNumReplays(1);
			mPlayer1->setNumReplays(1);
			if (counter >= 0)
			{
				healthbar[counter]->setShow(false);
				counter -= 1;
			}
		}
		// Toogle full screen when pressing "space"
		//if (mI->_input->onKeyPress(IND_SPACE)) mI->_render->toggleFullScreen();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	// ----- Free -----

	mI->end();

	return 0;
}