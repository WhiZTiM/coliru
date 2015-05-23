function tick()  
      local playerPed = PLAYER.PLAYER_PED_ID()
    local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	if(playerExists) then
		if(PED.IS_PED_IN_ANY_VEHICLE(playerPed, false)) then
			local veh = PED.GET_VEHICLE_PED_IS_IN(playerPed,true)
			if(get_key_pressed(97)) then
				VEHICLE.SET_VEHICLE_FORWARD_SPEED(veh,1200)
				local testmodule = {}
 
function tick()
        local playerPed = PLAYER.PLAYER_PED_ID()
        local player = PLAYER.GET_PLAYER_PED(playerPed)
        local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
        if(PLAYER.IS_PLAYER_ONLINE() and playerExists) then
                if(get_key_pressed(76)) then
                        local playerPed = PLAYER.PLAYER_PED_ID();
                        local coords = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 5.0, 0.0);
                        local clone = PED.CREATE_RANDOM_PED(coords.x, coords.y, coords.z);
                        local group = PLAYER.GET_PLAYER_GROUP(PLAYER.PLAYER_ID());
                        PED.SET_PED_AS_GROUP_MEMBER(clone, group);
                        AI.TASK_COMBAT_HATED_TARGETS_AROUND_PED(clone, 5000, 0);
                        PED.SET_PED_KEEP_TASK(clone, true);
                        WEAPON.GIVE_DELAYED_WEAPON_TO_PED(clone, GAMEPLAY.GET_HASH_KEY("weapon_pistol50"), 5, true);
                        ENTITY.SET_ENTITY_INVINCIBLE(clone, false);
                       
                end
                               
                               
                               
                               
                               
                               
        end
end
			end
		end
	end
end 