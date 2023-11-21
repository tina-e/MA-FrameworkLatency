#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import wx

WIDTH = 1920
HEIGHT = 1200

class TestApp(wx.Frame):
    def __init__(self, *args, **kw):
        super(TestApp, self).__init__(*args, **kw)

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)

        self.color = '#000000'

        self.SetTitle("framework")
        self.ShowFullScreen(True)

    def OnPaint(self, e):
        dc = wx.PaintDC(self)

        dc.SetBrush(wx.Brush(self.color))
        dc.SetPen(wx.TRANSPARENT_PEN)
        dc.DrawRectangle(0, 0, WIDTH, HEIGHT)

    def OnClick(self, e):
        self.color = '#FFFFFF'
        e.Skip()
        self.Refresh()

    def OnRelease(self, e):
        self.color = '#000000'
        e.Skip()
        self.Refresh()

def main():
    app = wx.App()
    test_app = TestApp(None)
    test_app.Show()
    app.MainLoop()


if __name__ == '__main__':
    main()
