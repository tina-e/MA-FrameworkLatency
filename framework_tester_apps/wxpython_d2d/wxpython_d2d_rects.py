#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import random
import wx

class TestApp(wx.Frame):
    def __init__(self, *args, **kw):
        super(TestApp, self).__init__(*args, **kw)
        self.renderer = wx.GraphicsRenderer.GetDirect2DRenderer()

        self.width = 1920
        self.height = 1080
        self.min_x_rects = 300

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)
        self.SetBackgroundColour(wx.BLACK)

        self.clicked = False
        self.SetBackgroundColour('#000000')
        self.SetTitle("framework")
        self.ShowFullScreen(True)

    def OnPaint(self, e):
        dc = wx.PaintDC(self)
        gc = self.renderer.CreateContext(dc)

        if self.clicked:
            for i in range(999):
                r = random.random()
                g = random.random()
                b = random.random()
                color = wx.Colour(int(r*255), int(g*255), int(b*255))
                brush = wx.Brush(color)
                gc.SetBrush(brush)
                x = random.randint(self.min_x_rects, self.width)
                y = random.randint(0, self.height)
                width = random.randint(0, self.width-x)
                height = random.randint(0, self.height-y)
                gc.DrawRectangle(x, y, width, height)
            gc.SetBrush(wx.Brush("white"))
            gc.SetPen(wx.TRANSPARENT_PEN)
            gc.DrawRectangle(0, 0, 300, 300)

        
    def OnClick(self, e):
        self.clicked = True
        self.Refresh()
        e.Skip()

    def OnRelease(self, e):
        self.clicked = False
        self.Refresh()
        e.Skip()

def main():
    app = wx.App()
    test_app = TestApp(None)
    #test_app.Show()
    app.MainLoop()


if __name__ == '__main__':
    main()
