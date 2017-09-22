#include "gtest/gtest.h"

#include "Core/Context.h"
#include "Core/Object.h"
#include "IO/File.h"
#include "IO/FileSystem.h"


using namespace Urho3D;

Context* ctx;
FileSystem* fs;

void Init()
{
	ctx = new Context();
	fs = new FileSystem(ctx);
	ctx->RegisterSubsystem(fs);
}


TEST(Base, FileParse)
{
	if (!ctx) {
		Init();
	}


}
