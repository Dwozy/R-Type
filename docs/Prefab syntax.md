# Prefab JSON Syntax

At the root of the prefab json file, you have to give the prefab a name and its components this way:
```json
{
    "name": "name",
    "components": [
        ...
    ]
}
```

Then, you can precise the components taken by the prefab this way:
```json
{
    "type": "NameOfTheComponent",
    "value": {
        "field1": 0,
        "field2": "foo",
        "field3": {
            "field4": "bar",
            "field5": 5
        }
    }
}
```

Here's the list of custom types in json syntax:
`Input::Keyboard::Key`
```json
"KeyName"
```

`Rect<T>`
```json
{
    "left": T,
    "top": T,
    "width": T,
    "height": T
}
```

`Vector2<T>`
```json
{
    "x": T,
    "y": T
}
```

`Texture`
```json
{
    "path": string,
    "area": Rect<int>
}
```

Here's the list of components supported in json syntax:
`TransformComponent`
```json
{
    "position": Vector2<float>,
    "velocity": Vector2<float>
}
```

`HealthComponent`
```json
{
    "health": int
}
```

`DamageComponent`
```json
{
    "damage": size_t
}
```

`ControllableComponent`
```json
{
    "key_up": Input::Keyboard::Key,
    "key_down": Input::Keyboard::Key,
    "key_left": Input::Keyboard::Key,
    "key_right": Input::Keyboard::Key,
    "speed": float
}
```

`TextureComponent`
```json
{
    "texturePath": string,
    "textureSize": Rect<int>,
    "textureRect": Rect<int>[],
    "animated": bool (optional: default false),
    "animationSpeed": float (optional: default: 0.0),
    "isRendered": bool (optional: default true),
    "lastUpdate": float (optional: default 0.0),
    "renderLayer": size_t
}
```

`CollisionComponent`
```json
{
    "collider": Rect<float>,
    "layer": size_t,
    "isActive": bool (optional: default true),
}
```

`GravityComponent`
```json
{
    "gravityForce": Vector2<float>,
    "isActive": bool,
}
```

`CameraComponent`
```json
{
    "cameraView": Rect<float>,
    "cameraViewport": Rect<float> (optional),
    "follow_x": bool (optional),
    "follow_y": bool (optional),
    "isActive": bool (optional),
}
```

`TextComponent`
```json
{
    "str": string,
    "size": float,
    "fontPath": string,
    "isRendered": bool (optional: default true),
    "renderLayer": size_t
}
```
