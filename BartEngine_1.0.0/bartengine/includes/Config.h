#ifndef BART_ENGINE_CONFIG_H
#define BART_ENGINE_CONFIG_H

#include <NullGraphic.h>
#include <NullAudio.h>
#include <NullInput.h>
#include <NullTimer.h>
#include <NullScene.h>
#include <NullLogger.h>
#include <NullCollision.h>

#include <SceneManager.h>
#include <BaseCollision.h>

#define BART_ENGINE_VERSION_MAJOR 1
#define BART_ENGINE_VERSION_MINOR 0
#define BART_ENGINE_VERSION_REVISION 0
#define BART_ENGINE_VERSION_STRING "1.0.0"

#define CREATE_SCENE(x) x = new SceneManager();
#define CREATE_COLLISION(x) x = new BaseCollision();

#define USE_SDL_ENGINE
#define DEBUG_CACHES 1
#define USE_VLD 0

#ifdef USE_SDL_ENGINE
#include <SdlGraphics.h>
#include <SdlAudio.h>
#include <SdlInput.h>
#include <SdlTimer.h>

#ifdef _DEBUG
#include <VsLogger.h>
#define CREATE_LOGGER(x) x = new VsLogger();
#else
#include <FileLogger.h>
#define CREATE_LOGGER(x) x = new FileLogger();
#endif

#define CREATE_GRAPHIC(x) x = new SdlGraphics();
#define CREATE_AUDIO(x) x = new SdlAudio();
#define CREATE_INPUT(x) x = new SdlInput();
#define CREATE_TIMER(x) x = new SdlTimer();

#else
#define USE_NULL_ENGINE

#define CREATE_GRAPHIC(x) x = new NullGraphic();
#define CREATE_AUDIO(x) x = new NullAudio();
#define CREATE_INPUT(x) x = new NullInput();
#define CREATE_TIMER(x) x = new NullTimer();

#endif

#define SAFE_CLEAN(x) if((x) != nullptr) (x)->Clean(); delete (x); (x) = nullptr;
#define SAFE_DELETE(x) if((x) != nullptr) delete (x); (x) = nullptr;
#endif
