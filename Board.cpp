#include "Board.h"

using namespace std;
using namespace DirectX;
using namespace std::chrono;


Board::Board(Graphics* pGFX,float BlockScale)
	:
	pGFX(pGFX) , BlockScale(BlockScale)
{
	this->proportion =  (float)pGFX->GetHeight()/ (float)pGFX->GetWidth();

	std::vector<Line> Lines;

	for (float y = BlockScale; y < 1.0f; y += BlockScale * 2.0f)
	{
		Lines.push_back(Line{ -1/ proportion, y, 0, 0, 0 });
		Lines.push_back(Line{ 1/ proportion, y, 0, 0, 0 });
	}
	for (float y = -BlockScale; y > -1.0f; y -= BlockScale * 2.0f)
	{
		Lines.push_back(Line{ -1/ proportion, y, 0, 0, 0 });
		Lines.push_back(Line{ 1/ proportion, y, 0, 0, 0 });
	}

	for (float x = BlockScale; x < 1.0f/proportion; x += BlockScale * 2)
	{
		Lines.push_back(Line{ x, -1, 0, 0, 0 });
		Lines.push_back(Line{ x, 1, 0, 0, 0 });
	}
	for (float x = -BlockScale; x > -1.0f/ proportion; x -= BlockScale * 2)
	{
		Lines.push_back(Line{ x, -1, 0, 0, 0 });
		Lines.push_back(Line{ x, 1, 0, 0, 0 });
	}

	VertexCount = Lines.size();
	ScreenBinds.push_back(new VertexBufferBind(move(Lines),pGFX));

	VertexShaderBind* VSshader = new VertexShaderBind(L"VanillaVertexShader.cso", pGFX);
	vector<D3D11_INPUT_ELEMENT_DESC> ied = 
	{
	{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,8,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	ScreenBinds.push_back(new InputLayoutBind(move(ied), VSshader->GetBlob(),pGFX));
	ScreenBinds.push_back(VSshader);

	ScreenBinds.push_back(new PixelShaderBind(L"VanillaPixelShader.cso", pGFX));

	PositionTransformer transforms;

	transforms.proportion = this->proportion;
	ScreenBinds.push_back(new VSConstantBufferBind(transforms, pGFX));
	ScreenBinds.push_back(new PrimitiveTopologyBind(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, pGFX));

	Mario = new Entity(pGFX, L"D:\\C++\\Programy C++\\2DGame\\Image\\Mario.png", 0, 0, BlockScale*0.9, BlockScale*0.9);
	Mario->SetUVCord(83, 94, 162, 178);

	Mario->BindCamera(cam);


	last = high_resolution_clock::now();
}

void Board::Controll(Window& wnd)
{

	while (!wnd.IsMouseEventEmpty())
	{
		const auto e = wnd.ReadMouseEvent();
		// Addind Block------------------------------------------------
		if (e.Type == Window::MouseEvent::Event::LeftPress && BuilderMode)
		{
			float PosX = wnd.GetMousePosXNormalized() / proportion;
			float PosY = wnd.GetMousePosYNormalized();

			int BlockNumbX = floor((PosX + BlockScale) / (BlockScale * 2));
			int BlockNumbY = ceil((PosY - BlockScale) / (BlockScale * 2));

			switch (switcher)
			{
			case Board::AddingElem::Block:
			    {
				GraphicalObject* NewRect = new GraphicalObject(pGFX, L"D:\\C++\\Programy C++\\2DGame\\Image\\Blocks.png",
					BlockNumbX * (BlockScale * 2) - cam.X, BlockNumbY * (BlockScale * 2) - cam.Y, BlockScale, BlockScale);

				NewRect->SetUVCord(97, 113, 1, 17);
				NewRect->BindCamera(cam);

				Blocks.push_back(NewRect);
			    }
				break;
			case Board::AddingElem::Creature:
			   {
				Creature* NewRect = new Creature(pGFX, L"D:\\C++\\Programy C++\\2DGame\\Image\\Beast.png",
					BlockNumbX * (BlockScale * 2) - cam.X, BlockNumbY * (BlockScale * 2) - cam.Y, BlockScale*0.9, BlockScale*0.9);

				NewRect->SetUVCord(0, 15, 16, 32);
				NewRect->BindCamera(cam);

				Monsters.push_back(NewRect);
			   }
				break;
			default:
				break;
			}

		}
		//Deleting block------------------------------------------------
		else if (e.Type == Window::MouseEvent::Event::RightPress && BuilderMode)
		{
			float PosX = wnd.GetMousePosXNormalized() / proportion;
			float PosY = wnd.GetMousePosYNormalized();

			int BlockNumbX = floor((PosX + BlockScale) / (BlockScale * 2));
			int BlockNumbY = ceil((PosY - BlockScale) / (BlockScale * 2));
			switch (switcher)
			{
				case Board::AddingElem::Block:
				{
					Blocks.remove_if(
						[BlockNumbX, BlockNumbY, this](GraphicalObject* block)
						{
							auto Rect = block->GetRect();

							float val1 = -BlockScale + BlockNumbX * (this->BlockScale * 2) - this->cam.X;
							float val2 = BlockScale + BlockNumbY * (this->BlockScale * 2) - this->cam.Y;

							bool Cond1 = abs(val1 - Rect.TopLeft.x) <= 0.03;
							bool Cond2 = abs(val2 - Rect.TopLeft.y) <= 0.03;

							if (Cond1 && Cond2)
							{
								delete block;
								return true;
							}
							else
							{
								return false;
							}
						});
				}
				break;
				case Board::AddingElem::Creature:
				{
					Monsters.remove_if(
						[BlockNumbX, BlockNumbY, this](Creature* creature)
						{
							auto Rect = creature->GetRect();

							float val1 = -BlockScale + BlockNumbX * (this->BlockScale * 2) - this->cam.X;
							float val2 = BlockScale + BlockNumbY * (this->BlockScale * 2) - this->cam.Y;

							bool Cond1 = abs(val1 - Rect.TopLeft.x) <= 0.03;
							bool Cond2 = abs(val2 - Rect.TopLeft.y) <= 0.03;

							if (Cond1 && Cond2)
							{
								delete creature;
								return true;
							}
							else
							{
								return false;
							}
						});
				}
				break;
			}
			
		}
		if (e.Type == Window::MouseEvent::Event::WheelPrees)
		{
			BuilderMode = !BuilderMode;
			wnd.ClearKeyEvent();
		}
	}
			
	if (BuilderMode)
	{
		if (wnd.IsKeyPressed(VK_UP))   cam.Y += -BlockScale * 2;
		if (wnd.IsKeyPressed(VK_DOWN)) cam.Y += BlockScale * 2;
		if (wnd.IsKeyPressed(VK_RIGHT))cam.X += -BlockScale * 2;
		if (wnd.IsKeyPressed(VK_LEFT)) cam.X += BlockScale * 2;


		while (!wnd.IsKeyboardEventEmpty())
		{
			const auto e = wnd.ReadKeyEvent();
			if (e.Type == Window::KeyEvent::Event::Press && e.Code == '1')
			{
				switcher = AddingElem::Block;
			}
			if (e.Type == Window::KeyEvent::Event::Press && e.Code == '2')
			{
				switcher = AddingElem::Creature;
			}
		}
	}

	// Time stuff

	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;

	// Collision and updating monsters pos 
	if (!BuilderMode)
	{
		for (auto creature : Monsters)
		{
			creature->UpdatePos(Blocks,frameTime.count());
		}
	}


	// Collision and updating mario pos
	if (!lost)
	{
		Mario->UpdatePos(wnd, frameTime.count(), cam, Blocks, BuilderMode);
		lost = Mario->ContactWithMonstet(Monsters,BlockScale);
	}
}


void Board::Draw()
{
	if (BuilderMode)
	{
		for (auto b : ScreenBinds)
		{
			b->Bind();
		}
		pGFX->Draw(VertexCount);
	}

	for (auto rect : Blocks)
	{
		rect->UpdateCamera(cam);
		rect->Draw();
	}

	for (auto creature : Monsters)
	{
		creature->UpdateCamera(cam);
		creature->Draw();
	}

	Mario->UpdateCamera(cam);
	Mario->Draw();
}
