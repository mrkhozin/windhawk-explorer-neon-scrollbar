// ==WindhawkMod==
// @id              explorer-neon-scroll-configurable
// @name            Explorer Cyber-Neon Scrollbar (Configurable Alpha Override)
// @description     Neon scrollbar with glow, with adjustable alpha override for suspicious areas.
// @version         0.7
// @author          Moch. Khozin & Copilot
// @include         explorer.exe
// @compilerOptions -lcomdlg32 -lgdiplus -luxtheme
// ==/WindhawkMod==
// ==WindhawkModReadme==
/*
/ # 🌀 Explorer Cyber-Neon Scrollbar (Kontrol Manual Alpha)

Mod ini menggambar efek neon di scrollbar Explorer dengan thumb hijau dan track ungu transparan.

📌 Catatan:
- Explorer menggunakan scrollbar yang sama untuk panel navigasi dan panel utama.
- Jika panel navigasi ikut terwarnai, turunkan nilai `track.alpha` ke 30–50 agar efeknya nyaris tak terlihat.
- Efek thumb tetap aktif dan terang.

🎨 Tips:
- `track.alpha = 120` → terlihat jelas
- `track.alpha = 30` → nyaris transparan
- `thumb.alpha = 230` → tetap neon

---

/ # 🌀 Explorer Cyber-Neon Scrollbar (Manual Alpha Control)

This mod draws neon effects on Explorer scrollbars with green thumb and translucent purple track.

📌 Notes:
- Explorer uses the same scrollbar for both navigation and main panels.
- If the navigation panel gets tinted, reduce `track.alpha` to 30–50 to make it nearly invisible.
- Thumb effect remains bright and active.

🎨 Tips:
- `track.alpha = 120` → clearly visible
- `track.alpha = 30` → nearly transparent
- `thumb.alpha = 230` → stays neon
*/
// ==WindhawkModReadme==

// ==WindhawkModSettings==
/*
- track:
  - red: 80
  - green: 0
  - blue: 70
  - alpha: 120
  $name: Track color (RGBA)
- thumb:
  - red: 0
  - green: 255
  - blue: 110
  - alpha: 230
  $name: Thumb color (RGBA)
- glow:
  - red: 0
  - green: 255
  - blue: 150
  - alpha: 160
  - size: 10
  $name: Glow config
- trackOverlayEnabled: true
  $name: Enable track overlay
- safeMode: true
  $name: Enable auto alpha override in suspicious areas
- overrideAlpha: 30
  $name: Override alpha value (0–255) for suspicious areas
- enabled: true
  $name: Mod enabled
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <gdiplus.h>
#include <uxtheme.h>

using namespace Gdiplus;

struct {
    BYTE track_r, track_g, track_b, track_a;
    BYTE thumb_r, thumb_g, thumb_b, thumb_a;
    BYTE glow_r, glow_g, glow_b, glow_a;
    int glow_size;
    bool trackOverlayEnabled;
    bool safeMode;
    BYTE overrideAlpha;
    bool enabled;
} settings;

void LoadSettings() {
    settings.track_r = (BYTE)Wh_GetIntSetting(L"track.red");
    settings.track_g = (BYTE)Wh_GetIntSetting(L"track.green");
    settings.track_b = (BYTE)Wh_GetIntSetting(L"track.blue");
    settings.track_a = (BYTE)Wh_GetIntSetting(L"track.alpha");

    settings.thumb_r = (BYTE)Wh_GetIntSetting(L"thumb.red");
    settings.thumb_g = (BYTE)Wh_GetIntSetting(L"thumb.green");
    settings.thumb_b = (BYTE)Wh_GetIntSetting(L"thumb.blue");
    settings.thumb_a = (BYTE)Wh_GetIntSetting(L"thumb.alpha");

    settings.glow_r = (BYTE)Wh_GetIntSetting(L"glow.red");
    settings.glow_g = (BYTE)Wh_GetIntSetting(L"glow.green");
    settings.glow_b = (BYTE)Wh_GetIntSetting(L"glow.blue");
    settings.glow_a = (BYTE)Wh_GetIntSetting(L"glow.alpha");
    settings.glow_size = Wh_GetIntSetting(L"glow.size");

    settings.trackOverlayEnabled = Wh_GetIntSetting(L"trackOverlayEnabled") != 0;
    settings.safeMode = Wh_GetIntSetting(L"safeMode") != 0;
    settings.overrideAlpha = (BYTE)Wh_GetIntSetting(L"overrideAlpha");
    settings.enabled = Wh_GetIntSetting(L"enabled") != 0;
}

bool IsThumbPart(int partId) {
    return partId == 2 || partId == 3;
}

bool IsTrackPart(int partId) {
    return partId >= 4 && partId <= 7;
}

bool IsSuspiciousRect(const RECT* r) {
    int w = r->right - r->left;
    int h = r->bottom - r->top;
    return (r->left < 150 && w > 1000 && h < 100);
}

void DrawRoundedRect(Graphics &g, const Rect &r, INT radius, const SolidBrush &brush) {
    GraphicsPath path;
    int x = r.X, y = r.Y, w = r.Width, h = r.Height;
    int d = radius * 2;
    if (w <= d || h <= d) {
        path.AddRectangle(r);
    } else {
        path.AddArc(x, y, d, d, 180, 90);
        path.AddArc(x + w - d, y, d, d, 270, 90);
        path.AddArc(x + w - d, y + h - d, d, d, 0, 90);
        path.AddArc(x, y + h - d, d, d, 90, 90);
        path.CloseFigure();
    }
    g.FillPath(&brush, &path);
}

void DrawOuterGlow(Graphics &g, const Rect &r, INT radius, const Color &glowColor, int glowSize) {
    for (int i = glowSize; i >= 1; --i) {
        BYTE alpha = (BYTE)((float)glowColor.GetA() * ((float)i / (float)glowSize) * 0.6f);
        Color c(alpha, glowColor.GetR(), glowColor.GetG(), glowColor.GetB());
        Pen pen(c, (REAL)i * 2.0f);
        pen.SetLineJoin(LineJoinRound);
        GraphicsPath path;
        int x = r.X - i, y = r.Y - i, w = r.Width + i*2, h = r.Height + i*2;
        int d = radius * 2 + i*2;
        if (w <= d || h <= d) {
            path.AddRectangle(Rect(x,y,w,h));
        } else {
            path.AddArc(x, y, d, d, 180, 90);
            path.AddArc(x + w - d, y, d, d, 270, 90);
            path.AddArc(x + w - d, y + h - d, d, d, 0, 90);
            path.AddArc(x, y + h - d, d, d, 90, 90);
            path.CloseFigure();
        }
        g.DrawPath(&pen, &path);
    }
}

ULONG_PTR g_gdiplusToken = 0;
using DrawThemeBackground_t = HRESULT (WINAPI *)(HTHEME, HDC, int, int, const RECT *, const RECT *);
DrawThemeBackground_t DrawThemeBackground_Original = nullptr;

HRESULT WINAPI DrawThemeBackground_Hook(HTHEME hTheme, HDC hdc, int partId, int stateId, const RECT *pRect, const RECT *pClipRect) {
    HRESULT hr = DrawThemeBackground_Original(hTheme, hdc, partId, stateId, pRect, pClipRect);
    if (!settings.enabled || !pRect) return hr;

    if (IsThumbPart(partId) || (settings.trackOverlayEnabled && IsTrackPart(partId))) {
        Graphics g(hdc);
        g.SetSmoothingMode(SmoothingModeAntiAlias);
        Rect r(pRect->left, pRect->top, pRect->right - pRect->left, pRect->bottom - pRect->top);

        if (IsTrackPart(partId) && r.Width > 10 && r.Height > 10) {
            BYTE alpha = settings.track_a;
            if (settings.safeMode && IsSuspiciousRect(pRect)) {
                alpha = settings.overrideAlpha;
            }
            Color trackColor(alpha, settings.track_r, settings.track_g, settings.track_b);
            SolidBrush trackBrush(trackColor);
            g.FillRectangle(&trackBrush, r);
        }

        if (IsThumbPart(partId)) {
            Color glowColor(settings.glow_a, settings.glow_r, settings.glow_g, settings.glow_b);
            DrawOuterGlow(g, r, 8, glowColor, settings.glow_size);

            Color thumbColor(settings.thumb_a, settings.thumb_r, settings.thumb_g, settings.thumb_b);
            SolidBrush thumbBrush(thumbColor);
            DrawRoundedRect(g, r, 8, thumbBrush);
        }
    }

    return hr;
}

BOOL Wh_ModInit() {
    LoadSettings();
    GdiplusStartupInput gdiplusStartupInput;
    if (GdiplusStartup(&g_gdiplusToken, &gdiplusStartupInput, NULL) != Ok) return FALSE;

    HMODULE ux = LoadLibrary(L"uxtheme.dll");
    if (!ux) return FALSE;

    FARPROC pDraw = GetProcAddress(ux, "DrawThemeBackground");
    if (!pDraw) return FALSE;

    Wh_SetFunctionHook((void*)pDraw, (void*)DrawThemeBackground_Hook, (void**)&DrawThemeBackground_Original);
    return TRUE;
}

void Wh_ModUninit() {
    if (g_gdiplusToken) {
        GdiplusShutdown(g_gdiplusToken);
        g_gdiplusToken = 0;
    }
}

void Wh_ModSettingsChanged() {
    LoadSettings();
}