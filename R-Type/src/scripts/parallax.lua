local entity

function Start(entity_id)
    entity = entity_id
end

function Update()
    local pos = get_position(entity)

    if pos ~= nil then
        if pos.x <= -200 then
            pos.x = pos.x + 398
        end
    end
end