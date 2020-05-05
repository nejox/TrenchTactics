
#include "../TrenchTactics/IRenderer.h"
#include "../TrenchTactics/RendererImpl.h"
#include "../TrenchTactics/SpriteText.h"
#include "../TrenchTactics/SpriteText.cpp"
#include "catch.hpp"


//funktioniert nicht die scheiße


TEST_CASE("Text is properly displayed")
{
 IRenderer& renderer = RendererImpl::instance();
renderer.init(600, 400, 16, false);
SpriteText* text = new SpriteText(10);
text->load("hallo welt");
text->render();

}


