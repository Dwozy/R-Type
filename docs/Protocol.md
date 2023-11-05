# Protocol for R-Type server/client exchange

### Data stucture:
Data must be sent to server in this format:

|Magic Number|PacketType|Payload Size|
|---|---|---|
|32-bit unsigned integer|8-bit unsigned integer|16-bit unsigned integer|

|Data body|
|---|
|See Below|

### Pascal string:

Pascal string (noted Pstring) are string not null terminated, with the number of character before the string.

|Size of string|String|
|---|---|
|16-bit unsigned integer|string (not null terminated)|

### Event types:
- #### Player related events:
    - #### TranformData*
      Data represent Transform component of a entity:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### EndGameData*
      Data represent End Game component of a entity:
      |id|
      |---|
      |8-bit unsigned integer|
    - #### ScoreData*
      Data represent score:
      |id|
      |---|
      |16-bit unsigned integer|
    - #### InputData*
      Data represent Controllable component of a entity:
      |id|inputId|state|
      |---|---|---|
      |16-bit unsigned integer|8-bit unsigned integer|8-bit unsigned integer|
    - #### ControllableData*
      Data represent Controllable component of a entity:
      |id|
      |---|
      |16-bit unsigned integer|Float|Float|
    - #### StatePlayerData*
      Data represent State of the player:
      |id|invincibility
      |---|---|
      |16-bit unsigned integer|8-bit unsigned integer|
    - #### CollisionData*
      |id|idCallback|rectLeft|rectTop|rectRight|rectHeight|layer|
      |---|---|---|---|---|---|---|
      |16-bit unsigned integer|8-bit unsigned integer|Float|Float|Float|Float|8-bit unsigned integer|
    - #### TextureData*
      |id||idTexture|idOrderTexture|rectLeft|rectTop|rectWidth|rectHeight|rectTextureLeft|rectTextureTop|rectTextureWidth|rectTextureHeight|renderLayer|isAnimated|animationSpeed|
      |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
      |16-bit unsigned integer|8-bit unsigned integer|8-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|16-bit unsigned integer|8-bit unsigned integer|8-bit unsigned integer|float|
    - #### MoveData*
      Data represent Move component of a entity:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### ShootData*
      Data represent Shoot entity:
      |id|x|y|dx|dy|
      |---|---|---|---|---|
      |16-bit unsigned integer|Float|Float|Float|Float|
    - #### TextureResponse*
      Data if texture need to be resend:
      |id|idTexture|
      |---|---|
      |16-bit unsigned integer|16-bit unsigned integer
    - #### CollisionResponse*
      Data if Collision need to be resend:
      |id|
      |---|
      |16-bit unsigned integer
