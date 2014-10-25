local M = Class(DisplayObject)

function M:init()
	self.super:init()

	local width, height = application:getScreenSize()
	local assets = application:getAssets()

	local button = Widget.Button.new({x = 100, y = 100, width = 100, height = 50})
		:addEventListener("Press", function(d, e) print("Button [Press]") end)
		:addEventListener("Release", function(d, e) print("Button [Release]") end)
		:addEventListener("Click", function(d, e) print("Button [Click]") end)
	self:addChild(button)
end

return M
