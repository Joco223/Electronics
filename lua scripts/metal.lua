function Run(States, Heats, Types, LocalState, LocalHeat, LocalRed, LocalGreen, LocalBlue)
	if LocalState == 0 then
		for k, v in pairs(States) do
			if v == 2 and Types[k] == 1 then
				LocalState = 2
				break
			end
		end
	elseif LocalState == 1 then
		LocalState = 0
	elseif LocalState == 2 then
		LocalState = 1
	end
	
	if LocalState == 2 then
		LocalRed = 255
		LocalGreen = 255
		LocalBlue = 150
	elseif LocalState == 1 then
		LocalRed = 128
		LocalGreen = 139
		LocalBlue = 97
	elseif LocalState == 0 then
		LocalRed = 26
		LocalGreen = 24
		LocalBlue = 35
	end

	return LocalState, LocalHeat, LocalRed, LocalGreen, LocalBlue
end