print("Outside of function")

    local test = 0

    function Start()
        print("Start function")
    end

    function Update()
        -- local tsf = get_transform_component()
        -- if tsf[2] ~= nil then
        --     tsf[2].position.x = 0
        -- end
        local pos = get_position(2)
        print(pos)
        -- local pos = get_pos(2)
        if pos ~= nil then
            pos.x = 0
        end
        -- print(pos)
        -- for i=1, #tsf do
        --     if tsf[i] ~= nil then
        --         print(tsf[i].position.x)
        --     end
        -- end
        -- local int = engine:get_int_component()
        -- for i=1, #int do
        --     if int[i] ~= nil then
        --         int[i] = int[i] + 1
        --         print("INT: ", int[i])
        --     end
        -- end
        -- print("Script update ", test)
        -- test = test + 1
    end
