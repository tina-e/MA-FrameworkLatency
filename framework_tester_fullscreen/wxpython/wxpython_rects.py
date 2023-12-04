#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import random
import wx

class TestApp(wx.Frame):
    def __init__(self, *args, **kw):
        super(TestApp, self).__init__(*args, **kw)

        self.width = 1920
        self.height = 1200
        self.min_x_rects = self.width / 2

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)
        self.SetBackgroundColour(wx.BLACK)

        self.clicked = False

        self.SetTitle("framework")
        self.ShowFullScreen(True)

    def OnPaint(self, e):
        dc = wx.PaintDC(self)

        if self.clicked:
            for i in range(1000):
                r = random.random()
                g = random.random()
                b = random.random()
                color = wx.Colour(int(r*255), int(g*255), int(b*255))
                brush = wx.Brush(color)
                dc.SetBrush(brush)
                x = random.randint(self.min_x_rects, self.width)
                y = random.randint(0, self.height)
                width = random.randint(0, self.width-x)
                height = random.randint(0, self.height-y)
                dc.DrawRectangle(x, y, width, height)
            dc.SetBrush(wx.Brush("white"))
            dc.SetPen(wx.TRANSPARENT_PEN)
            dc.DrawRectangle(0, 0, 300, 300)
        else:
            dc.SetBrush(wx.Brush("black"))
            dc.SetPen(wx.TRANSPARENT_PEN)
            dc.DrawRectangle(0, 0, self.width, self.height)

        
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
    test_app.Show()
    app.MainLoop()


if __name__ == '__main__':
    main()
