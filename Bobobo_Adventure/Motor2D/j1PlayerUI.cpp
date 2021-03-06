#include "j1PlayerUI.h"
#include "j1Gui.h"
#include "j1App.h"

#include "j1MainMenuScene.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Player.h"
#include "j1FadeToBlack.h"
#include "j1UIItems.h"


j1PlayerUI::j1PlayerUI(){}
j1PlayerUI::~j1PlayerUI(){}

bool j1PlayerUI::Start()
{
	heart = App->gui->CreateImage(POSITION_LEFT, "textures/Heart.png", { 0, 0, 44, 41 }, { 30, 30 });
	Coin = App->gui->CreateImage(POSITION_LEFT, "textures/Coin.png", { 0, 0, 38, 36 }, { 30, 700 });
	LifeCounter = App->gui->CreateText(POSITION_LEFT, "a", { 80, 25 }, SLKSCR, {255,255,255,255});
	CoinCounter = App->gui->CreateText(POSITION_LEFT, "a", { 80, 695 }, SLKSCR, { 255,255,255,255 });
	PointCounter = App->gui->CreateText(POSITION_RIGHT, "a", { -300, 25 }, SLKSCR, { 255,255,255,255 });
	TimeCounter = App->gui->CreateText(POSITION_RIGHT, "a", { -100, 75 }, SLKSCR, { 255,255,255,255 });
	return true;
}

bool j1PlayerUI::Update(float dt)
{
	if (App->scene->active == true && App->scene2->active == false)
	{
		 if (App->enty->player->timestart > App->scene->sctime) {

			timescene = {"%i", App->scene->sctime + App->enty->player->timestart };
		TimeCounter->UpdateText(timescene);
		}
		else {
			timescene = { "%i", App->scene->sctime};
			TimeCounter->UpdateText(timescene);
			
		}
			
	}
	else if (App->scene2->active == true && App->scene->active== false)
	{
		if (App->enty->player->timestart > App->scene2->sc2time) {

			timescene = { "%i", App->scene2->sc2time + App->enty->player->timestart };
			TimeCounter->UpdateText(timescene);
		}
		else {
			timescene = { "%i", App->scene2->sc2time };
			TimeCounter->UpdateText(timescene);
		}

	}
	
	player_coins = { "%i", App->enty->player->numberofcoins };
	player_lifes = { "x %i", App->enty->player->playerlifes };
	player_points = { "Score %i", App->enty->player->playerpoints };

	if (App->enty->player->numberofcoins >= 10) {
		App->enty->player->playerlifes++;
		App->enty->player->numberofcoins = 0;
	}

	LifeCounter->UpdateText(player_lifes);
	CoinCounter->UpdateText(player_coins);
	PointCounter->UpdateText(player_points);

	
	return true;
}

bool j1PlayerUI::CleanUp()
{
	if (heart != nullptr){
		heart->CleanUp();
	}
	if (Coin != nullptr){
		Coin->CleanUp();
	}
	if (LifeCounter != nullptr){
		LifeCounter->CleanUp();
	}
	if (TimeCounter != nullptr){
		TimeCounter->CleanUp();
	}
	if (CoinCounter != nullptr){
		CoinCounter->CleanUp();
	}
	if (PointCounter != nullptr){
		PointCounter->CleanUp();
	}
	if (window != nullptr){
		window->CleanUp();
	}
	return true;
}
