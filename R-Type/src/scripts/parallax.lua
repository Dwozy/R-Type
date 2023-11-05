local entity

function Start(entity_id)
    print("Start function", entity_id)
    entity = entity_id
end

function Update()
    local pos = get_position(entity)

    if pos ~= nil then
        if pos.x <= -200 then
            pos.x = 199
        end
    end
end