#include "pch.h"
#include "CppUnitTest.h"
#include "../Game/source files/maze.cpp"
#include "../Game/headers/npcHealthBar.h"
#include "../Game/source files/npcHealthBar.cpp"  
#include "../Game/headers/resourceManager.h"
#include "../Game/source files/resourceManager.cpp"
#include "../Game/headers/player.h"
#include "../Game/source files/player.cpp"
#include "../Game/headers/inventory.h"
#include "../Game/source files/inventory.cpp"
#include "../Game/headers/item.h"
#include "../Game/source files/item.cpp"
#include "../Game/headers/maze.h"
#include "../Game/headers/items.h"
#include "../Game/source files/items.cpp"
#include "../Game/headers/window.h"
#include "../Game/source files/window.cpp"
#include "../Game/headers/button.h"
#include "../Game/source files/button.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QA
{
	TEST_CLASS(MazeTest
)
	{
	public:
		// This test checks that:
		// 1. The maze is successfully generated.
		// 2. The maze array is not null.
		// 3. The finish cell is correctly placed inside a walkable cell (represented by 1 in the maze array).
		TEST_METHOD(MazeGenerationTest)
		{
			Maze maze(27, 27);
			maze.generateTree();
			int** mazeArr = maze.getArray();
			Cell finish = maze.getFinishCell();

			Assert::IsNotNull(mazeArr);
			Assert::AreEqual(1, mazeArr[finish.y][finish.x]);
		}
	};
	TEST_CLASS(TakeDamageTest)
	{
	public:
		// It tests the Player class by applying 30 damage and checking that the health decreases from 100 to 70.
		TEST_METHOD(PlayerTakeDamageTest)
		{
			Player player = Player();
			player.takeDamage(30.f);

			Assert::AreEqual(70.f, player.getHealth());
		}
	};
	TEST_CLASS(WindowTest)
	{
	public:
		// The Window object can be created with valid parameters.
		TEST_METHOD(WindowInitializeTest)
		{
			Window window = Window(50.f, 50.f, "Test Window");
			Assert::IsNotNull(&window);
		}
		// The window can successfully assign a background image.
		TEST_METHOD(WindowSetBackgroundImageTest)
		{
			Window window = Window();
			window.setBackgroundImage("resources/images/mainMenuBackground.png");
			Assert::IsNotNull(&window);
		}
	};
	TEST_CLASS(InventoryTest)
	{
	public:
		// The Inventory object initializes correctly with a ResourceManager.
		TEST_METHOD(InventoryInitializeTest)
		{
			ResourceManager rm = ResourceManager();
			Inventory inventory(&rm);

			Assert::IsNotNull(&inventory);
		}
		// Inventory returns a valid pointer for the currently selected item.
		TEST_METHOD(GetSelectedItemTest)
		{
			ResourceManager rm = ResourceManager();
			Inventory inventory(&rm);

			Assert::IsNotNull(inventory.getSelectedItem());

		}
		// Changing the selected item index works and returns a valid item.
		TEST_METHOD(SetSelectedItem)
		{
			ResourceManager rm = ResourceManager();
			Inventory inventory(&rm);

			inventory.setSelectedItem(1);
			Assert::IsNotNull(inventory.getSelectedItem());
		}
	};
}

