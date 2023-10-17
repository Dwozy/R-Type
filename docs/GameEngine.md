# Game Engine documentation and usage

## Entity Component System

The Entity Component System is the core of the game engine, it will manage every entity and their components, and will update them with the systems.

The Components and Systems needs to be registered in the registry contained in the game engine.

The game engine already have some components and systems, but more can be created.

### Components

Components are ```struct``` that contains datas for the entities. They can be added to the registry using the ```RegisterComponent``` method.
To add them to an entity, use the ```AddComponent``` method.

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

#### TextComponent

|Name|Type|Description|
|---|---|---|
|str|std::string|String for the text.|
|size|std::size_t|Size of the text.|
|text|GameEngine::Text|Text class which will be rendered.|
|isRendered|bool|Tells whether the text should be rendered or not.|
|renderLayer|std::size_t|Priority for the rendering of the text, the lowest layer is render first.|

#### TextureComponent

|texture|GameEngine::Texture||
