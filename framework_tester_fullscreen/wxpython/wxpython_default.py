#!/usr/bin/python3

# this program is based on tutorials by ZetCode
# https://zetcode.com/wxpython

import wx
import time
import sys
import signal
import pandas

WIDTH = 1920
HEIGHT = 1200
click_timestamps = []

class TestApp(wx.Frame):
    def __init__(self, *args, **kw):
        super(TestApp, self).__init__(*args, **kw)
        
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnClick)
        self.Bind(wx.EVT_LEFT_UP, self.OnRelease)

        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.OnTimer)
        self.timer.Start()

        self.color = '#000000'

        self.SetTitle("framework")
        self.ShowFullScreen(True)
        self.Show()

    def OnTimer(self, event):
        pass

    def OnPaint(self, e):
        dc = wx.PaintDC(self)

        dc.SetBrush(wx.Brush(self.color))
        dc.SetPen(wx.TRANSPARENT_PEN)
        dc.DrawRectangle(0, 0, WIDTH, HEIGHT)

    def OnClick(self, e):
        click_timestamps.append(time.time())
        self.color = '#FFFFFF'
        e.Skip()
        self.Refresh()

    def OnRelease(self, e):
        self.color = '#000000'
        e.Skip()
        self.Refresh()


def signal_handler(signal, frame):
    print("signal wx")
    df = pandas.DataFrame(data={"wxpython": click_timestamps})
    df.to_csv("../../data/clicks/wxpython.csv", sep=',',index=False)
    sys.exit(0)

def main():
    app = wx.App()
    test_app = TestApp(None)
    signal.signal(signal.SIGTERM, signal_handler)
    signal.signal(signal.SIGINT, signal_handler)
    app.MainLoop()


if __name__ == '__main__':
    main()
    