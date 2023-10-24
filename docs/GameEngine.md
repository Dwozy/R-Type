# Game Engine documentation and usage

## Entity Component System

The Entity Component System is the core of the game engine, it will manage every entity and their components, and will update them with the systems.

The Components and Systems needs to be registered in the registry contained in the game engine.

The game engine already have some components and systems, but more can be created.

### Components

Components are ```struct``` that contains datas for the entities. They can be added to the registry using the ```RegisterComponent``` method.
To add them to an entity, use the ```AddComponent``` method.
The components are stored in ```SparseArray```s, these arrays store the components and can have empty indexes. Use the ```getComponent``` method of the registry to retrieve the array. Before using an index, you need to verify that the index have a value :
```cpp
SparseArray<int> &intArray = registry.getComponent<int>();

if (intArray[i])
    /// Use the value
```

#### Camera component

|Name|Type|Description|
|---|---|---|
|View|GameEngine::View|Will be used as the view for the window, needs to be set to it. It will define the scale of the camera.|

#### Collision component

|Name|Type|Description|
|---|---|---|
|collider|GameEngine::Rectf|Hitbox for the collision, the shape is a rect, and his position is based on the position in the transform component.|
|actions|std::vector<std::function<void(const std::size_t &entityId)>>|Vector storing the collision callbacks. They can be added using the ```addAction``` method|
|layer|std::size_t|Defines the layer of the collision, so the callbacks can be with only a certain layer of collisions|
|isActive|bool|Tells if the collision is active.|

#### ControllableComponent

|Name|Type|Description|
|---|---|---|
|key_up|GameEngine::Input::Keyboard::Key|Store the key which will be used to go up.|
|key_left|GameEngine::Input::Keyboard::Key|Store the key which will be used to go left.|
|key_down|GameEngine::Input::Keyboard::Key|Store the key which will be used to go down.|
|key_right|GameEngine::Input::Keyboard::Key|Store the key which will be used to go right.|
|speed|float|Speed to add to the velocity.|

#### FontComponent

|Name|Type|Description|
|---|---|---|
|path|std::string|Path to the font file.|
|font|GameEngine::Font|Font to use.|

#### MusicComponent

|Name|Type|Description|
|---|---|---|
|path|std::string|Path to the sound file.|
|music|GameEngine::Music|Music to use.|

#### PressableComponent

|Name|Type|Description|
|---|---|---|
|hitbox|GameEngine::Rect<int>|Rectangle for the hitbox of the pressable.|
|textureDefault|GameEngine::Rect<int>|Rectangle for the default state of the button. The texture needs to be a spritesheet, and the rectangle diffines the place of the sprite in it.|
|textureHovered|GameEngine::Rect<int>|Rectangle for the hovered state of the button, will trigger when the mouse is on the button but the button isn't pressed.|
|texturePressed|GameEngine::Rect<int>|Rectangle for the pressed state of the button.|
|state|GameEngine::PressableState|Enum which will be used to tell the state of the button.|
|action|std::function<void()>|Function for the callback of the button when pressed. Can store a lambda, which call another function with different parameters|

#### TextComponent

|Name|Type|Description|
|---|---|---|
|str|std::string|String for the text.|
|size|std::size_t|Size of the text.|
|text|GameEngine::Text|Text class which will be rendered.|
|isRendered|bool|Tells whether the text should be rendered or not.|
|renderLayer|std::size_t|Priority for the rendering of the text, the lowest layer is render first.|

#### TextureComponent

|Name|Type|Description|
|---|---|---|
|texture|GameEngine::Texture|Texture for the sprite.|
|sprite|GameEngine::Sprite|Sprite of the texture.|
|animated|bool|Tells if the texture is animated.|
|textureRects|std::vector<GameEngine::Rect<int>>|Rectangle deffining the different state of the animation in the texture.|
|animationSpeed|float|Speed of the update for the animation.|
|isRendered|bool|Tells whether the texture should be rendered or not.|
|lastUpdate|float|Last update of the texture.|
|animeId|std::size_t|Index of the animation in the vector.|
|renderLayer|std::size_t|Priority for the rendering of the text, the lowest layer is render first.|

#### TransformComponent

|Name|Type|Description|
|---|---|---|
|position|GameEngine::Vector2<float>|Position of the entity.|
|velocity|GameEngine::Vector2<float>|Velocity of the entity.|

### Systems

The systems can be functions, lambdas or classes which implements the ```operator()``` overload.
They can take ```SparseArray```s as parameter, and they will be automatically be passed when you register them using the ```addSystem``` method of the registry.
To use your added systems in the game loop, call the ```runSystems``` method of the registry. Systems will be called in the same order as when they were added.
Example of a system addition and run :
```c++
GameEngine::PositionSystem positionSystem(_gameEngine.deltaTime.getDeltaTime());

gameEngine.registry.addSystem<std::function<void(SparseArray<GameEngine::TransformComponent> &, SparseArray<GameEngine::TextureComponent> &)>,
GameEngine::TransformComponent, GameEngine::TextureComponent>(positionSystem);

// Game loop
while (1)
    gameEngine.registry.runSystems();
```

#### AnimeSystem

This system will handle the animation of the texture. The class takes a reference to the DeltaTime and the method that overload the ```operator()``` takes as parameter the ```TextureComponent```'s ```SparseArray```.

#### CollisionSystem

This system calls all the callback functions contained in the ```CollisionComponent``` if the collision is active. It takes as parameter the ```CollisionComponent```'s ```SparseArray```.

#### ControlSystem

This system updates the velocity of the entity based on the inputs. It takes as parameter the ```TransformComponent``` and ```ControllableComponent```'s ```SparseArray```.

#### DrawSystem

This system draws the entity texture and text on the screen based on the ```renderLayer```. It takes as parameter the ```TextComponent``` and ```TextureComponent```'s ```SparseArray```.
This system have to be register with the second method which takes an ```std::shared_ptr``` conataining the system class.

#### PositionSystem

This system updates the position of the entity based on the velocity and moves the entity's texture if the entity have one. It takes as parameter the ```TransformComponent``` and ```TextureComponent```'s ```SparseArray```.

#### PressableComponent

This system updates the state of the pressable and calls the callback action if the button is pressed. It takes as parameter the ```TransformComponent```, ```TextureComponent``` and ```PressableComponent```'s ```SparseArray```.

## Game engine

The game engine class is a class containing all the classes that the game needs.

### EventManager

Class managing events to comunicate in the game engine.
Each event can have one or more callbacks that will be called when the event is published.

Each event types are described in the ```Event``` enum with the type ```EventType```.

An ```EventHandler``` is a class that manages the callbacks of one specific event.

When the user want to use the event system, it needs to instantiate an ```EventManager``` and then use the ```addHandler``` method to add an handler (```EventHandler```) for each event that he wants to use.

The ```addHandler``` method take as template the type of the data that will be passed to the callbacks when the event is published and as parameter the type of the event that will be managed.

Event handler exemple

```cpp
// Create the event manager
GameEngine::EventMananger eventManager;

// Add a new event handler for the 'MyEvent' event
eventManager.addHandler<struct MyCallbackDataType>(GameEngine::Event::MyEvent);
```

To add a callback to an event the user must get the handler of the event and then use the ```subscribe``` methode and give the callback function.
The callback function must take as parameter the type given in the template of the addHandler methode.

Add event callback exemple

```cpp
void myCallback(struct MyCallbackDataType)
{
    // Do something
}

// Get the handler of the event
GameEngine::EventHandler<struct MyCallbackDataType> myHandler =  eventManager.getHandler<struct MyCallbackDataType>(GameEngine::Event::MyEvent)

// Add a callback function
myHandler.subscribe(myCallback);
MyCallbackDataType
```

Then now if the user wants to call the callbacks of the event he must call the ```publish``` methode

Publish event exemple
```cpp
// Pass the data to the callbacks
myHandler.publish(MyCallbackDataType());
```

### Registry

This is the Entity Component System described above.

### DeltaTime

Class which handles the delta time, it needs to be update at the begininf of the game loop with the method ```update```. To get the delta time, simply use the ```getDeltaTime``` method.

### SceneManager

Class managing scenes for the game, the scene needs to inherit the ```AScene``` class, and is used to create all the entity of a scene when it is loaded.

## Game loop example

```cpp
GameEngine::GameEngine gameEngine();

// Register components and systems

// Spawn entities and add the components
// Or
gameEngine.sceneManager.registerScene("Game", std::make_unique<GameScene>());
gameEngine.sceneManager.loadScene("Game");

while (gameEngine.window.isOpen()) {
    gameEngine.deltaTime.update();
    _gameEngine.registry.runSystems();
}
```
