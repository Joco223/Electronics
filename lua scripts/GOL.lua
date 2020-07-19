function Run(States, Heats, LocalState, LocalHeat, LocalRed, LocalGreen, LocalBlue)
	sum = 0

	for k, v in pairs(States) do
		sum = sum + v
	end

	if (sum < 2 or sum > 3) and LocalState == 1 then
		LocalState = 0
	end

	if LocalState == 0 and sum == 3 then
		LocalState = 1
	end

	if LocalState == 1 then
		LocalRed = 255
		LocalGreen = 255
		LocalBlue = 255
	else
		LocalRed = 0
		LocalGreen = 0
		LocalBlue = 0
	end

	return LocalState, LocalHeat, LocalRed, LocalGreen, LocalBlue
end