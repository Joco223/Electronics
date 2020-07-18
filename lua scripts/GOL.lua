function Run(TopLeftState, TopLeftHeat, TopState, TopHeat, TopRightState, TopRightHeat, LeftState, LeftHeat, RightState, RightHeat, BottomLeftState, BottomLeftHeat, BottomState, BottomHeat, BottomRightState, BottomRightHeat, LocalState, LocalHeat, LocalRed, LocalGreen, LocalBlue)
	sum = 0

	if TopLeftState == 1 then
		sum = sum + 1
	end

	if TopState == 1 then
		sum = sum + 1
	end

	if TopRightState == 1 then
		sum = sum + 1
	end

	if LeftState == 1 then
		sum = sum + 1
	end

	if RightState == 1 then
		sum = sum + 1
	end

	if BottomLeftState == 1 then
		sum = sum + 1
	end

	if BottomState == 1 then
		sum = sum + 1
	end

	if BottomRightState == 1 then
		sum = sum + 1
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

	return LocalBlue, LocalGreen, LocalRed, LocalHeat, LocalState
end