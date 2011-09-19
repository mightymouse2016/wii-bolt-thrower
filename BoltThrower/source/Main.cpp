// Bolt Thrower for the wii - Paul Overy - 2010

/* 
Bolt Thrower - Games design notes

* Players can guide asteroids, by placing proximity mines or any other method like ramming
* Offensive weapons
	- Effector � uses highly-efficient & sophisticated technology, doubles up as a defensive weapon 
* Defensive weapons
	- Chaff dispenser - cheap and easy to resource
* Background effect - Comets with dust trail

* Mechanisms of War
	- A material defeat happens when the ability to fight is lost
	- A mental defeat happens when the will to fight is lost
	- Reduced ability affects the will to fight, and reduced will affects the ability to fight
* Decisive action (quick), or by attrition (slow)
	- Decisive action is meant to defeat the enemy in a relatively short period of maximum effort, which in itself contributes to defeating the enemy by rapid destruction, and by shocking some of its forces and neutralizing others. It's a good way to defeat a stronger enemy or to defeat the enemy with minimal losses, but sometimes it's simply not possible, depending on the situation. 
	- Attrition is meant to defeat the enemy by gradually eroding its resources (and/or morale) at a rate higher than its rate of recovery, and of course at the same time by not being eroded even faster at your side. A war of attrition is a slow and often very bloody business, but if decisive action is not possible it's the only way left. The best (and bloodiest) example of attrition is World War 1 where millions of lives were lost and the only benefit was that the enemy was running out of soldiers a bit faster. 
	(A blockade is a common way of attrition. It sometimes has the potential of being so successful in damaging the enemy that it might quickly become a decisive action that will suffocate the enemy's war potential and end the war.  )
	
	Defeat can be achieved either by attacking and defeating the enemy's strong points (which might save the need to also attack the rest of its force) or weak points (which saves the need to attack its strong points).
	
	Detecting the enemy's weak points or detecting an enemy key strong point worthy of being attacked is one of the main goals of the various types of intelligence units, from plain combat observers to codebreakers and spies. 

	The enemy is often generally aware of its weaknesses, and if knows early enough which one will be attacked it can often reinforce it and neutralize the attack. That's why surprise and deception are often so important in attack and even in defense, and why secrecy is so important in not letting the enemy gather information about your side, your weaknesses, and your intentions. 

* The four mechanisms of defeat
	- The ability to fight is defeated either by destruction
	- or by paralysis. 
	- The will to fight is defeated either by loss of interest in the cause 
	- or by loss of faith in the ability to achieve it. 

'The Mechanisms Of Defeat': see (http://www.2worldwar2.com/mechanisms-of-defeat.htm)
	
*/

#include <gccore.h>
#include "config.h"
#include "Singleton.h"
#include "WiiManager.h"
#include "Image.h"
#include "InputDeviceManager.h"
#include "GameLogic.h"
#include "Menu.h"
#include "debug.h"
#include "Util.h"
#include "Util3d.h"

#include "HashString.h"
#include <math.h>
#include "WiiFile.h"
#include <asndlib.h>
#include <gcmodplay.h>
#include "FontMAnager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "JPEGDEC.h"

#include "Image.h"
#include "GameDisplay.h"
#include "MenuScreens.h"

//#include  "HTTP/HTTP_Util.h"

#include <network.h>

#include  "URIManager.h"


#include <ogc/machine/processor.h>
#include <ogc/lwp_watchdog.h>
#include "ogc/lwp.h"
#include <ogcsys.h>

#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>



#include "oggplayer/oggplayer.h"


extern "C" {  extern void __exception_setreload(int t); }

extern void OggTest();

//
////Wiilight stuff  
//static vu32 *_wiilight_reg = (u32*)0xCD0000C0;  
//void wiilight(int enable) 
//{            
// // Toggle wiilight (thanks Bool for wiilight source)     
//  u32 val = (*_wiilight_reg&~0x20);      
//  if (enable && Settings.wiilight) 
//  val |= 0x20;      *_wiilight_reg=val; 
//}    
//


#include "CullFrustum\Vec3.h"
#include "CullFrustum\FrustumR.h"

int main(int argc, char **argv) 
{	
	__exception_setreload(6);
	WiiManager& rWiiManager( Singleton<WiiManager>::GetInstanceByRef() );
	rWiiManager.InitWii();

	rWiiManager.ProgramStartUp();
	rWiiManager.SetGameState(WiiManager::eIntro);

	MODPlay_Init(&rWiiManager.m_ModuleTrackerPlayerInterface);
	rWiiManager.m_ModuleTrackerPlayerInterface.playing = false;


//NOTE
//pthread_create priority number (last param) must be >0 and <=127, typically 64
//the stack can be changed to a smaller value but note it is unusually easy to eat up the stack. The define size is recommended
//please dont change the define as libogc recommends 8k.
//
// UNIX has 128 priorites which range from 0 - high to 127 -low.)
	
{
	//static char IP[16]; // i.e. 255.255.255.255 + NULL
	//s32 result( if_config(IP, NULL, NULL, true) );   // this calls net_init() in a nice way (must provide first param)
	//if(result < 0) 
	//	ExitPrintf("if_config failed");

	//pURLManager->SaveURI("http://www.dr-lex.be/software/download/mp3tones.zip", Util::GetGamePath() );
	//pURLManager->SaveURI("http://vba-wii.googlecode.com/files/Visual%20Boy%20Advance%20GX%202.2.5.zip");
	//pURLManager->SaveURI("http://www.fnordware.com/superpng/pngtest8rgba.png");

	//MemoryInfo* pMeminfo( pURLManager->NewFromURI("http://wiimc.googlecode.com/files/WiiMC%201.2.0%20%28New%20Install%29.zip") );
	//pMeminfo->SavePath("c://");
	//delete pMeminfo;

//	rWiiManager.GetURLManager()->SaveURI("http://he3.magnatune.com/all/09-Faerie%20tale-Indidginus.ogg", Util::GetGamePath());
//	rWiiManager.GetSoundManager()->LoadSound(Util::GetGamePath() + "09-Faerie tale-Indidginus.ogg", "Indidginus");



}




	bool ModPlaying = false;  // modplay's own interface (Interface.playing) does not seem to work, even if I set it
	bool bQuit = false;
	do
	{
		if (!ModPlaying)
		{
			ModPlaying = true;

			rWiiManager.m_ModuleTrackerPlayerInterface.manual_polling=false;  
			MODPlay_SetMOD(&rWiiManager.m_ModuleTrackerPlayerInterface, rWiiManager.m_pModuleTrackerData);
			MODPlay_Start(&rWiiManager.m_ModuleTrackerPlayerInterface); 
			MODPlay_SetVolume( &rWiiManager.m_ModuleTrackerPlayerInterface, 10,10);    

	//rWiiManager.SetGameState(WiiManager::eGame);   // this is shit ... disable sounds needed, not this fudge
	//rWiiManager.GetSoundManager()->PlaySound( (HashLabel)"Indidginus",244,244,true );
	//rWiiManager.SetGameState(WiiManager::eIntro); 
		}




		rWiiManager.GetGameLogic()->InitialiseGame();
		
		//rWiiManager.GetCamera()->SetCameraView( 0,0 );

		rWiiManager.GetCamera()->SetCameraView( 0, 0, -(579.4f));

		rWiiManager.GetGameLogic()->ClearBadContainer();
		rWiiManager.GetGameLogic()->InitialiseIntro();

		if (rWiiManager.IsGameStateShowingIntro())
		{

			//--------------
			// INTRO
			do 
			{	
				if (Util::IsPowerOff()) //if ( g_bEnablePowerOffMode )
				{
					extern int g_PowerOffMode;
					::SYS_ResetSystem( g_PowerOffMode, 0, 0 );
				}
				rWiiManager.GetGameLogic()->Intro();

				if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_HOME)!= 0 )
				{
					bQuit = true;
					break;
				}

			if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_1)!= 0 )
			{
	rWiiManager.SetGameState(WiiManager::eGame);   // this is shit ... disable sounds needed, not this fudge

	{
		OggPlayer Ogg;
	string FullFileName = Util::GetGamePath() + "09-Faerie tale-Indidginus.ogg";
	FILE* pOggFile( WiiFile::FileOpenForRead( FullFileName.c_str() ) );
	u32 OggSize = WiiFile::GetFileSize(pOggFile);
	u8* pOggData = (u8*) malloc(OggSize);
	fread( pOggData, OggSize, 1, pOggFile);
	Ogg.PlayOgg(pOggData, OggSize, 0, OGG_ONE_TIME);

//	int fd = open (FullFileName.c_str(), O_WRONLY);
//	PlayOgg(&fd, 0, 0, OGG_ONE_TIME);

	}
	rWiiManager.SetGameState(WiiManager::eIntro); 
				
			}


			} while( (WPAD_ButtonsUp(0) & (WPAD_BUTTON_A | WPAD_BUTTON_B) )== 0 );
		}

		if (bQuit)
			break;

		//--------------
		// MENU
		rWiiManager.SetGameState(WiiManager::eMenu);
		rWiiManager.GetCamera()->SetCameraView( 0, 0, -(579.4f));
		rWiiManager.GetMenuScreens()->SetTimeOutInSeconds();

		if (rWiiManager.IsGameStateShowingMenu())
		{
			do 
			{	
				if (Util::IsPowerOff()) //if ( g_bEnablePowerOffMode )
				{
					extern int g_PowerOffMode;
					::SYS_ResetSystem( g_PowerOffMode, 0, 0 );
				}

				if (rWiiManager.IsGameStateShowingMenu())
				{
					rWiiManager.GetMenuManager()->SetMenuGroup("MainMenu");
					rWiiManager.GetMenuScreens()->DoMenuScreen();

					if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_B) || (rWiiManager.GetMenuScreens()->HasMenuTimedOut()) )  
					{
						rWiiManager.SetGameState(WiiManager::eIntro);
						break;
					}

					if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_A) != 0) 
					{
						HashLabel Name = rWiiManager.GetMenuManager()->GetSelectedMenu();

						if (Name == HashString::Quit)
						{
							bQuit = true;
						}
						else if (Name == HashString::Credits)
						{
							rWiiManager.SetGameState(WiiManager::eCredits);
						}
						else if (Name == HashString::Controls)
						{
							rWiiManager.SetGameState(WiiManager::eControls);
						}
						else if (Name == HashString::Options)
						{
							rWiiManager.SetGameState(WiiManager::eOptions);
						}
						else if (Name == HashString::Start_Game)
						{
							rWiiManager.SetGameState(WiiManager::eGame);
							break;
						}
						else if (Name == HashString::Intro)
						{
							rWiiManager.SetGameState(WiiManager::eIntro);
							break;
						}
					}
				}
			
				if (rWiiManager.IsGameStateShowingCredits())
				{
					rWiiManager.GetMenuScreens()->DoCreditsScreen();
					if ( WPAD_ButtonsUp(0) & (WPAD_BUTTON_A|WPAD_BUTTON_B) )
					{
						rWiiManager.GetMenuScreens()->SetTimeOutInSeconds();
						rWiiManager.SetGameState(WiiManager::eMenu);
					}
				}

				if (rWiiManager.IsGameStateShowingControls())
				{
					rWiiManager.GetMenuScreens()->DoControlsScreen();
					if ( WPAD_ButtonsUp(0) & (WPAD_BUTTON_A|WPAD_BUTTON_B) )
					{
						rWiiManager.GetMenuScreens()->SetTimeOutInSeconds();
						rWiiManager.SetGameState(WiiManager::eMenu);
					}
				}
				
				if (rWiiManager.IsGameStateShowingOptions())
				{
					rWiiManager.GetMenuScreens()->DoOptionsScreen();		
					rWiiManager.GetMenuManager()->SetMenuGroup("OptionsMenu");
					if ( WPAD_ButtonsUp(0) & (WPAD_BUTTON_A|WPAD_BUTTON_B) )
					{
						HashLabel Name = rWiiManager.GetMenuManager()->GetSelectedMenu();		

						rWiiManager.GetMenuManager()->SetMenuGroup("OptionsMenu");

						if (Name == (HashLabel)"Ingame_Music")
						{
							rWiiManager.GetMenuManager()->AdvanceMenuItemText(HashString::IngameMusicState);
						}
						else if (Name == (HashLabel)"Difficulty_Level")
						{
							rWiiManager.GetMenuManager()->AdvanceMenuItemText(HashString::DifficultySetting);
						}
						else if (Name == (HashLabel)"Set_Language")
						{
							rWiiManager.GetMenuManager()->AdvanceMenuItemText(HashString::LanguageSetting);
							rWiiManager.SetLanguage( rWiiManager.GetMenuManager()->GetMenuItemText(HashString::LanguageSetting) );
						}
						else if ((Name == (HashLabel)"Back") || ( WPAD_ButtonsUp(0)&WPAD_BUTTON_B ))
						{
							rWiiManager.GetMenuScreens()->SetTimeOutInSeconds();
							rWiiManager.SetGameState(WiiManager::eMenu);
						}
						rWiiManager.BuildMenus( true );
					}
				}

				if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_HOME)!= 0 )
					bQuit = true;

			} while (!bQuit);
		}

		if (bQuit)
			break;

		//----------------
		// PLAY GAME
		if (rWiiManager.IsGameStateShowingGame())
		{
			// Ingame music - settings
			rWiiManager.GetMenuManager()->SetMenuGroup("OptionsMenu");
			if (rWiiManager.GetMenuManager()->GetMenuItemText(HashString::IngameMusicState) == "on")
			{
				MODPlay_SetVolume( &rWiiManager.m_ModuleTrackerPlayerInterface, 35,35);     
			}
			else
			{
				ModPlaying = false;  // looks like the modplay interface is lacking a few minor things
				MODPlay_Stop(&rWiiManager.m_ModuleTrackerPlayerInterface);
			}

			rWiiManager.GetGameLogic()->InitialiseGame();

			WPAD_ScanPads();   // Do a read now, this will flush out anything old ready for a fresh start.
			bool bEndLevel = false;
			do // game loop
			{

				rWiiManager.GetGameLogic()->InGameLogic();
				if ( rWiiManager.GetGameLogic()->IsEndLevelTrigger() )
				{
					if (!rWiiManager.IsGameStateShowingGame())
					{
						bEndLevel = true;
					}
					if (WPAD_ButtonsUp(0) & WPAD_BUTTON_A)
					{
						bEndLevel = true;
					}
				}

				if ( (WPAD_ButtonsUp(0) & WPAD_BUTTON_HOME)!= 0 )
				{
					bQuit = true;
				}
			} while( !bEndLevel && !bQuit );
		}
	} while( !bQuit );
	
	rWiiManager.GetGameDisplay()->DisplaySimpleMessage("Bye...");

	//////for (int i=0 ;i<2; ++i)
	//////{
	//////	Util3D::TransRot(0,0,-3.14f/12.0f);
	//////	rWiiManager.GetFontManager()->DisplayLargeTextCentre("bye", 0,0,112);
	//////	GX_SetZMode (GX_TRUE, GX_LEQUAL, GX_TRUE);
	//////	rWiiManager.SwapScreen();  // to clear zbuffer keep GX_SetZMode on until after this call 
	//////}
	rWiiManager.UnInitWii();
	return 0;
}
static lwp_t networkthread = LWP_THREAD_NULL;
static bool networkHalt = true;
static bool exitRequested = false;
static u8 * ThreadStack = NULL;
static bool networkinit = false;


static void * networkinitcallback(void *arg )
{
	while(!exitRequested)
	{
		if(networkHalt)
		{
			LWP_SuspendThread(networkthread);
			usleep(100);
			continue;
		}

		////if(!networkinit)
		////	Initialize_Network();

		//if(!firstRun)
		//{
		//	ConnectSMBShare();
		//	if(Settings.FTPServer.AutoStart)
		//		FTPServer::Instance()->StartupFTP();

		//	ConnectFTP();
		//	CheckForUpdate();

		//	LWP_SetThreadPriority(networkthread, 0);
		//	firstRun = true;
		//}

		//if(Receiver.CheckIncomming())
		//{
		//	IncommingConnection(Receiver);
		//}

		usleep(200000);
	}
	return NULL;
}
void ResumeNetworkThread()
{
	networkHalt = false;
	LWP_ResumeThread(networkthread);
}


void InitNetworkThread()
{
	ThreadStack = (u8 *) memalign(32, 16384);
	if(!ThreadStack)
		return;

	LWP_CreateThread (&networkthread, networkinitcallback, NULL, ThreadStack, 16384, 30);
	ResumeNetworkThread();
}

void ShutdownNetworkThread()
{
	//Receiver.FreeData();
	//Receiver.CloseConnection();
	exitRequested = true;

	if(networkthread != LWP_THREAD_NULL)
	{
		ResumeNetworkThread();
		LWP_JoinThread (networkthread, NULL);
		networkthread = LWP_THREAD_NULL;
	}

	if(ThreadStack)
		free(ThreadStack);
	ThreadStack = NULL;
}







//////
//////void DisplaySimpleMessage(std::string Text)
//////{
//////	Util3D::Trans(0,0);
//////	rWiiManager.GetCamera()->SetCameraView( 0, 0, -(579.4f));
//////
//////	for (int i=0 ;i<2; ++i)
//////	{
//////		Util3D::TransRot(0,0,-3.14f/12.0f);
//////		rWiiManager.GetFontManager()->DisplayLargeTextCentre(Text, 0,0,112);
//////		GX_SetZMode (GX_TRUE, GX_LEQUAL, GX_TRUE);
//////		rWiiManager.SwapScreen();  // to clear zbuffer keep GX_SetZMode on until after this call 
//////	}
//////}


//inline float absf(float f)
//{
//	volatile float tmp = f; 
//	// This MUST be "volatile"! Without it the compiler will try to
//	// optimize it and ends up using 13 instructions!
//	asm("fabs 	  %0, %0     		\n\t" 
//		 :   "=f" (tmp)             //output        
//		 :   "f"  (tmp)             //input
//	);	
//	return tmp;
//}



// Buzz words for web search
//
//// Interpolation methods
//
//double LinearInterpolate(
//   double y1,double y2,
//   double mu)
//{
//   return(y1*(1-mu)+y2*mu);
//}
//
//Linear interpolation results in discontinuities at each point. 
//Often a smoother interpolating function is desirable, perhaps the simplest is cosine interpolation. 
//A suitable orientated piece of a cosine function serves to provide a smooth transition between adjacent segments. 
//
//double CosineInterpolate(
//   double y1,double y2,
//   double mu)
//{
//   double mu2;
//
//   mu2 = (1-cos(mu*PI))/2;
//   return(y1*(1-mu2)+y2*mu2);
//}



	//for (int i=0; i<Wii.GetXmlVariable(HashString::AsteroidTotal); ++i)
	//{
	////	static const int Width (800000);
	////	static const int Height(800000);

	//	float ang = M_PI; //(rand()%(int)(M_PI*2.0f*1000.0f))/1000.0f;
	//	float r = rand()%AsteroidRadius;
	//	float x = sin(ang) * r;
	//	float y = cos(ang) * r;

	//	Asteroid.SetPos( x, y, (-50000 + rand()%100000)*0.01f );

	//	Asteroid.SetRotateAmount(	(5000-(rand()%10000)) * 0.0000065f, 
	//								(5000-(rand()%10000)) * 0.0000065f, 
	//								(5000-(rand()%10000)) * 0.0000065f );
	//	m_AsteroidContainer->push_back(Asteroid);
	//}