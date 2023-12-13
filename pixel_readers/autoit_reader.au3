$coordX = 5
$coordY = 5


While 1
	If _IsPressed('01') Then
		$iTime = TimerInit()
		While GetColorValue() <> 255
			Sleep(1)
		WEnd
		$time_diff = Int(TimerDiff($iTime))
		ConsoleWrite($time_diff & @CRLF)
	EndIf
WEnd


Func GetColorValue()
	$pixelColor = PixelGetColor($coordX, $coordY)
	$colorValue = BitAND($pixelColor, 0xFF)
	ConsoleWrite($colorValue & @CRLF)
	return $colorValue
EndFunc


; https://www.autoitscript.com/forum/topic/8982-detect-mouse-click/
Func _IsPressed($HexKey)
   Local $AR
   $HexKey = '0x' & $HexKey
   $AR = DllCall("user32","int","GetAsyncKeyState","int",$HexKey)
   If NOT @Error And BitAND($AR[0],0x8000) = 0x8000 Then Return 1
   Return 0
EndFunc
