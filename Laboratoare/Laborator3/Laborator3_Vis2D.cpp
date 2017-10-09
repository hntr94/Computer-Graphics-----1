#include "Laborator3_Vis2D.h"

#include <vector>
#include <iostream>

#include <Windows.h>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Score.h"
#include "Gift.h"

#define MAX_ENEMIES 9
#define VELOCITY 50

#define BULLET_RADIUS 10
#define PLAYER_RADIUS 75
#define ENEMY_RADIUS 75
#define BIG_ENEMY_RADIUS 120
#define PI 3.141592652

using namespace std;

Laborator3_Vis2D::Laborator3_Vis2D()
{
}

Laborator3_Vis2D::~Laborator3_Vis2D()
{
}

// Create player
Player* player = new Player(PLAYER_RADIUS);

vector<Enemy*> enemies;
vector<Bullet*> bullets;
vector<Gift*> gifts;
Score* score = new Score();
double time = 0, logicX = 0, logicY = 0;
double ship_time = 0, scale_time = 0, gift_time = 0, invulnerable_time = 0, bullet_time = 0;
bool clicked_on_mouse, more_bullets = false;
double delta = 2.0;
float var = 0.0f, deltaScale = 0.0f;
float mx, my;
int counter = 0;

void Laborator3_Vis2D::Init()
{
	glm::ivec2 resolution = window->GetResolution();


	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	logicSpace.x = -1000;		// logic x
	logicSpace.y = -1000;		// logic y
	logicSpace.width = 2000;	// logic width
	logicSpace.height = 2000;	// logic height

	viewSpace.x = 0;
	viewSpace.y = 0;

	viewSpace.width = resolution[0];
	viewSpace.height = resolution[1];

	
	// Sets the screen area where to draw
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0), true);

	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

	

	//////////////////
	//player
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(50, 50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(50, -50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-50, -50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-50, 50, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 4
		};

		// Create a new mesh from buffer data
		meshes["player"] = CreateMesh("player", vertices, indices);
	}

	//enemies
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(50, 50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(50, -50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-50, -50, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(-50, 50, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 4
		};

		// Create a new mesh from buffer data
		meshes["enemy"] = CreateMesh("enemy", vertices, indices);
	}

	//BIG ENEMIES
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 0, 0)),
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 3, 4
		};

		// Create a new mesh from buffer data
		meshes["gift"] = CreateMesh("gift", vertices, indices);
	}

	// bullets
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 0, 0)),
			//VertexFormat(glm::vec3(-50, 50, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		// Create a new mesh from buffer data
		meshes["bullet"] = CreateMesh("bullet", vertices, indices);
	}

	//lives
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 20, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(20, 0, 0), glm::vec3(1, 0, 0)),
			//VertexFormat(glm::vec3(-50, 50, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			0, 2, 3
		};

		// Create a new mesh from buffer data
		meshes["lives"] = CreateMesh("lives", vertices, indices);
	}

}


Mesh* Laborator3_Vis2D::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	// TODO: Create the VAO and bind it

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;	// ID-ul (nume sau referinta) buffer-ului ce va fi cerut de la GPU
	glGenBuffers(1, &VBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// TODO: Send vertices data into the VBO buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);


	// TODO: Send indices data into the IBO buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This is section is strongly linked to how the GPU Shader program treats data
	// It will be learned later, when GLSL shaders will introduces
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

// 2D visualization matrix
glm::mat3 Laborator3_Vis2D::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}

// uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Laborator3_Vis2D::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Laborator3_Vis2D::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Laborator3_Vis2D::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Laborator3_Vis2D::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	if (score->lives == 0) {
		// DOOM
		
		time = Engine::GetElapsedTime();

	}
	else {
		// Compute uniform 2D visualization matrix
		modelMatrix = glm::mat3(1);
		modelMatrix *= visMatrix;
		
		// change the player angle
		glm::vec3 pos = visMatrix * glm::vec3(player->x, player->y, 0);
		player->angle = atan2(my - pos.y, mx - pos.x) + PI /2;
 
		// move player to new position
		modelMatrix *= Transform2D::Translate(player->x, player->y);
		modelMatrix *= Transform2D::Rotate(player->angle);

		// check for 5 seconds invulnerability
		if (invulnerable_time + 5 < Engine::GetElapsedTime()) {
			player->invulnerable = false;
		}
		//change player color if invulnerable
		if(!player->invulnerable)
			RenderMesh2D(meshes["player"], modelMatrix, glm::vec3(0.0f, 0.9f, 0.1f));
		else {
			RenderMesh2D(meshes["player"], modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		// Bullets
		int i;
			//check if you have multiple bullets for max 10 seconds
		if (bullet_time + 10 < Engine::GetElapsedTime()) {
			more_bullets = false;
		}

		// move bullets to new positions
		// check if they are out of boundaries and if so, eliminate them
		for (i = 0; i < bullets.size(); i++) {

			modelMatrix = glm::mat3(1);
			modelMatrix *= visMatrix;
			modelMatrix *= Transform2D::Translate(bullets[i]->x, bullets[i]->y);
			bullets[i]->x += (cos(bullets[i]->angle) * bullets[i]->velocity);
			bullets[i]->y += sin(bullets[i]->angle) * bullets[i]->velocity ;
			if (bullets[i]->x > 2000 || bullets[i]->y > 1000 || bullets[i]->x < -2000 || bullets[i]->y < -1000) {
				bullets.erase(bullets.begin() + i);
				if (i > 0) i--;
			} 
			RenderMesh2D(meshes["bullet"], modelMatrix, glm::vec3(0.0f, 0.8f, 1.0f));

		}

		// get a random degree and then transform it to radians
		int n = rand() % 360;
		
		// generate a random enemy on an imaginary circle (player centered)
		// give them random speeds
		if (ship_time + delta < Engine::GetElapsedTime() && enemies.size() < MAX_ENEMIES) {
			enemies.push_back(new Enemy(player->x + 1000 * cos(n * PI/180.0), player->y + 1000 * sin(n* PI/180.0), rand()%3, 5 + rand()%5, 1));
			counter++;
			// setup if it's a big enemy
			if (enemies[enemies.size() -1]->type == 1) {
				enemies[enemies.size() -1]->setScale(1.5);
				enemies[enemies.size() -1]->setColor(1.0f, 1.0f, 0.0f);
				enemies[enemies.size() -1]->setLife(2);
				enemies[enemies.size() -1]->setRadius(BIG_ENEMY_RADIUS);
				
			}
			// setup if it's a simple
			else if (enemies[enemies.size() -1]->type == 0 ) {
				enemies[enemies.size() -1]->setScale(1);
				enemies[enemies.size() -1]->setColor(0.0f, 0.0f, 1.0f);
				enemies[enemies.size() -1]->setLife(1);
				enemies[enemies.size() - 1]->setRadius(ENEMY_RADIUS);
			}
			// setup if it's a scindable enemy
			else if (enemies[enemies.size() - 1]->type == 2) {
				enemies[enemies.size() - 1]->setScale(1);
				enemies[enemies.size() - 1]->setColor(0.2f, 0.5f, 0.5f);
				enemies[enemies.size() - 1]->setLife(2);
				enemies[enemies.size() - 1]->setRadius(BIG_ENEMY_RADIUS);
			}
			// time for big to small enemy animation
			if (delta > 0.5)
				delta -= 0.1;
			ship_time = Engine::GetElapsedTime();
			
		}

		// move enemies to a new location
		// rotate them to follow the player
		for (i = 0; i < enemies.size(); i++) {
			int j;
			

			modelMatrix = glm::mat3(1);

			modelMatrix *= visMatrix;

			enemies[i]->angle = atan2(player->y - enemies[i]->y, player->x - enemies[i]->x) + PI/2;
			//enemies[i]->x += (player->x - enemies[i]->x) * 0.01 * enemies[i]->velocity;
			//enemies[i]->y += (player->y - enemies[i]->y) * 0.01 * enemies[i]->velocity;

			enemies[i]->x += cos(enemies[i]->angle - PI/2) * enemies[i]->velocity ;
			enemies[i]->y += sin(enemies[i]->angle - PI/2) * enemies[i]->velocity ;

			modelMatrix *= Transform2D::Translate(enemies[i]->x, enemies[i]->y);
			
			modelMatrix *= Transform2D::Rotate(enemies[i]->angle);
			modelMatrix *= Transform2D::Scale(enemies[i]->scale,enemies[i]->scale);


			
			// enemy-bullet collision
			for (j = 0; j < bullets.size(); j++) {
				if (!enemies.empty()) {
					if (sqrt(pow(enemies[i]->x - bullets[j]->x, 2) + pow(enemies[i]->y - bullets[j]->y, 2)) <= enemies[i]->radius + bullets[j]->radius + 10) {
						
							if (enemies[i]->type == 0 || enemies[i]->lives == 1) {
								enemies.erase(enemies.begin() + i);
								
							}
							else if (enemies[i]->type == 1){
								enemies[i]->lives--;
								enemies[i]->setColor(1.0, 0.0, 0.0);
								enemies[i]->gotHit = true;
								enemies[i]->setVelocity(2*enemies[i]->velocity);
								enemies[i]->setRadius(BIG_ENEMY_RADIUS/2);
							}
							else if (enemies[i]->type == 2) {
								enemies.push_back(new Enemy(enemies[i]->x - 100, enemies[i]->y - 100, 0, 1, 1));
								enemies[enemies.size() - 1]->setScale(0.75);
								enemies[enemies.size() - 1]->setColor(0.5f, 1.0f, 1.0f);
								enemies[enemies.size() - 1]->setVelocity(2 + rand()%3);
								enemies[enemies.size() - 1]->setLife(1);
								enemies[enemies.size() - 1]->setRadius(ENEMY_RADIUS);
								
								enemies.push_back(new Enemy(enemies[i]->x - 100, enemies[i]->y + 100, 0, 1, 1));
								enemies[enemies.size() - 1]->setScale(0.75);
								enemies[enemies.size() - 1]->setColor(0.5f, 1.0f, 1.0f);
								enemies[enemies.size() - 1]->setVelocity(2 + rand() % 3);
								enemies[enemies.size() - 1]->setLife(1);
								enemies[enemies.size() - 1]->setRadius(ENEMY_RADIUS);

								enemies.erase(enemies.begin() + i);
								//if (i > 0) i--;

							}
							if (i > 0) i--;
							bullets.erase(bullets.begin() + j);
						
					}
				}
			}
		
			// enemy collision
			// get remaining lives if player gets hit
			if (!enemies.empty()) {
				if (sqrt(pow(enemies[i]->x - player->x, 2) + pow(enemies[i]->y - player->y, 2)) <= enemies[i]->radius + player->radius + 10) {
					enemies.erase(enemies.begin() + i);
					if(!player->invulnerable)
						score->decrement();
					if (i > 0) i--;
				}
			}

			
			// scale the big enemies if they get hit (animation)
			if (!enemies.empty()) {
				if (enemies[i]->gotHit == true) {
					if (enemies[i]->scale > 0.75) {
						enemies[i]->scale -= 0.05;
					}
				}
				RenderMesh2D(meshes["enemy"], modelMatrix, glm::vec3(enemies[i]->red, enemies[i]->green, enemies[i]->blue));
			}
			
		}
	

		// render the remaining lives
		int j;
		for (j = 0; j < score->lives; j++) {
			modelMatrix = glm::mat3(1);

			modelMatrix *= visMatrix;
			modelMatrix *= Transform2D::Translate(resolution.x + 100 - j * 45, resolution.y + 100);
			modelMatrix *= Transform2D::Rotate(PI / 4);
			modelMatrix *= Transform2D::Scale(3, 4);

			RenderMesh2D(meshes["bullet"], modelMatrix, glm::vec3(0.5f, 0.0f, 0.0f));
		}

		// generate random gifts on random positions, with specific colors
		// -invulnerability
		// -one more life
		// -5-directional bullets
		if (gift_time + 10 < Engine::GetElapsedTime()) {
			int k1 = rand() % 2 ;
			int k2 = rand() % 2 ;
			if (0 == k1) k1 = -1;
			if (0 == k2) k2 = -1;
			gifts.push_back(new Gift(rand()%resolution.x * k1, rand() % resolution.y * k2, rand()%3, BULLET_RADIUS * 4));
			if(gifts[gifts.size() -1]->type == 0)
				gifts[gifts.size() - 1]->setColor(1.0, 1.0, 1.0);
			if (gifts[gifts.size() - 1]->type == 1)
				gifts[gifts.size() - 1]->setColor(0.0, 1.0, 1.0);
			if (gifts[gifts.size() - 1]->type == 2)
				gifts[gifts.size() - 1]->setColor(1.0, 0.0, 1.0);
			gift_time = Engine::GetElapsedTime();
		}

		// put gifts to their place
		for (i = 0; i < gifts.size(); i++) {


			modelMatrix = glm::mat3(1);

			modelMatrix *= visMatrix;
			modelMatrix *= Transform2D::Translate(gifts[i]->x, gifts[i]->y);
			modelMatrix *= Transform2D::Scale(4, 4);

			// gift collision
			if (sqrt(pow(gifts[i]->x - player->x, 2) + pow(gifts[i]->y - player->y, 2)) <= gifts[i]->radius + player->radius + 10) {
				if (gifts[i]->type == 2) {
					score->lives++;
				}
				if (gifts[i]->type == 0 && player->invulnerable == false) {
					invulnerable_time = Engine::GetElapsedTime();
					player->invulnerable = true;
				}
				if (gifts[i]->type == 1) {
					bullet_time = Engine::GetElapsedTime();
					more_bullets = true;
				}


				gifts.erase(gifts.begin() + i);
				if (i > 0) i--;
			}
			// render the gifts
			if (!gifts.empty()) 
				RenderMesh2D(meshes["bullet"], modelMatrix, glm::vec3(gifts[i]->r, gifts[i]->g, gifts[i]->b));
		}
	}

	//ending animation
	if (time + 2 > Engine::GetElapsedTime() && time != 0) {
		var += 0.005;
		glClearColor(var, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
}

void Laborator3_Vis2D::FrameEnd()
{

}

void Laborator3_Vis2D::OnInputUpdate(float deltaTime, int mods)
{
	
	if (window->KeyHold(GLFW_KEY_W)) {
		player->y += 25;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		player->x -= 25;
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		player->y -= 25;
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		player->x += 25;
	}


}

void Laborator3_Vis2D::OnKeyPress(int key, int mods)
{
	
}

void Laborator3_Vis2D::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3_Vis2D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	// add mouse move event
	glm::ivec2 resolution = window->GetResolution();
	my = resolution.y / 2 - mouseY;
	mx = mouseX - resolution.x / 2;
	//player->angle = atan2( ( - (mouseY - (-player->y * resolution.y/logicSpace.height + resolution.y/2))), (mouseX - ( resolution.x/2) - player->x * resolution.x/logicSpace.width )) + 3.141592652/2 ;
	//player->angle = atan2(-(mouseY - (logicSpace.y + player->y * (logicSpace.height / viewSpace.y))), mouseX - (logicSpace.x + player->x * (logicSpace.width / viewSpace.x)));

}

void Laborator3_Vis2D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	glm::ivec2 resolution = window->GetResolution();
	clicked_on_mouse = true;

	if (!more_bullets) {
		bullets.push_back(new Bullet(player->x, player->y));
		//bullets[bullets.size() - 1]->angle = atan2((-(mouseY - (player->y * resolution.y / logicSpace.height + resolution.y/2 ))), (mouseX - (resolution.x / 2) - player->x * resolution.x / logicSpace.width)) ;
		bullets[bullets.size() - 1]->angle = player->angle - PI / 2;
		bullets[bullets.size() - 1]->velocity = VELOCITY;
		bullets[bullets.size() - 1]->radius = BULLET_RADIUS;
	}
	else {
		bullets.push_back(new Bullet(player->x, player->y));
		bullets.push_back(new Bullet(player->x, player->y));
		bullets.push_back(new Bullet(player->x, player->y));
		bullets.push_back(new Bullet(player->x, player->y));
		bullets.push_back(new Bullet(player->x, player->y));

		bullets[bullets.size() - 1]->angle = player->angle - PI / 2 + PI/6;
		bullets[bullets.size() - 2]->angle = player->angle - PI / 2;
		bullets[bullets.size() - 3]->angle = player->angle - PI / 2 - PI/6;
		bullets[bullets.size() - 4]->angle = player->angle - PI / 2 - PI / 12;
		bullets[bullets.size() - 5]->angle = player->angle - PI / 2 + PI / 12;

		bullets[bullets.size() - 1]->velocity = VELOCITY;
		bullets[bullets.size() - 1]->radius = BULLET_RADIUS;
		bullets[bullets.size() - 2]->velocity = VELOCITY;
		bullets[bullets.size() - 2]->radius = BULLET_RADIUS;
		bullets[bullets.size() - 3]->velocity = VELOCITY;
		bullets[bullets.size() - 3]->radius = BULLET_RADIUS;
		bullets[bullets.size() - 4]->velocity = VELOCITY;
		bullets[bullets.size() - 4]->radius = BULLET_RADIUS;
		bullets[bullets.size() - 5]->velocity = VELOCITY;
		bullets[bullets.size() - 5]->radius = BULLET_RADIUS;
	}
	
	// add mouse button press event
}

void Laborator3_Vis2D::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3_Vis2D::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}