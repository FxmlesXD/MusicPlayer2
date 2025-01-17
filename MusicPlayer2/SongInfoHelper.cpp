﻿#include "stdafx.h"
#include "SongInfoHelper.h"
#include "Common.h"
#include "AudioCommon.h"
#include "MusicPlayer2.h"

CString CSongInfoHelper::GetBitrateString(const SongInfo& song)
{
    CString str;
    if (song.bitrate == 0)
    {
        str = _T("-");
    }
    else
    {
        str.Format(_T("%d kbps"), song.bitrate);
    }
    return str;
}

CString CSongInfoHelper::GetChannelsString(const SongInfo& song)
{
    CString chans_str;
    if (song.channels == 0)
        chans_str = _T("-");
    if (song.channels == 1)
        chans_str = CCommon::LoadText(IDS_MONO);
    else if (song.channels == 2)
        chans_str = CCommon::LoadText(IDS_STEREO);
    else if (song.channels == 6)
        chans_str = CCommon::LoadText(_T("5.1 "), IDS_CHANNEL);
    else if (song.channels == 8)
        chans_str = CCommon::LoadText(_T("7.1 "), IDS_CHANNEL);
    else if (song.channels > 2)
        chans_str.Format(CCommon::LoadText(_T("%d "), IDS_CHANNEL), song.channels);
    return chans_str;
}

CString CSongInfoHelper::GetFreqString(const SongInfo& song)
{
    CString freq;
    if (song.freq == 0)
        freq = _T("-");
    else
        freq.Format(_T("%.1f kHz"), song.freq / 1000.0f);
    return freq;
}

CString CSongInfoHelper::GetBitsString(const SongInfo& song)
{
    CString bits;
    if (song.bits == 0)
        bits = CCommon::LoadText(IDS_UNDEFINED);
    else
        bits.Format(_T("%d Bit"), song.bits);
    return bits;
}

void CSongInfoHelper::SetSongChannelInfo(SongInfo& song, const ChannelInfo& channel_info)
{
    song.bitrate = channel_info.bitrate;
    song.bits = static_cast<BYTE>(channel_info.bits);
    song.freq = channel_info.freq;
    song.channels = static_cast<BYTE>(channel_info.channels);
}

CSongInfoHelper::ChannelInfo CSongInfoHelper::GetSongChannelInfo(const SongInfo& song)
{
    ChannelInfo channel_info;
    channel_info.bitrate = song.bitrate;
    channel_info.bits = song.bits;
    channel_info.freq = song.freq;
    channel_info.channels = song.channels;
    return channel_info;
}

std::wstring CSongInfoHelper::GetDisplayStr(const SongInfo& song_info, DisplayFormat display_format)
{
    AudioType type{ CAudioCommon::GetAudioTypeByFileName(song_info.file_path) };
    if (type == AU_MIDI)		//MIDI只显示文件名
    {
        display_format = DF_FILE_NAME;
    }
    switch (display_format)
    {
    case DF_FILE_NAME:		//显示为文件名
        return song_info.GetFileName();
    case DF_TITLE:			//显示为歌曲标题
        if (song_info.IsTitleEmpty())	//如果获取不到歌曲标题，就显示文件名
            return song_info.GetFileName();
        else
            return song_info.title;
    case DF_ARTIST_TITLE:	//显示为艺术家 - 标题
        if (song_info.IsTitleEmpty() && song_info.IsArtistEmpty())		//如果标题和艺术家都获取不到，就显示文件名
            return song_info.GetFileName();
        else
            return (song_info.GetArtist() + _T(" - ") + song_info.GetTitle());
    case DF_TITLE_ARTIST:	//显示为标题 - 艺术家
        if (song_info.IsTitleEmpty() && song_info.IsArtistEmpty())		//如果标题和艺术家都获取不到，就显示文件名
            return song_info.GetFileName();
        else
            return (song_info.GetTitle() + _T(" - ") + song_info.GetArtist());
    default:
        return song_info.GetFileName();
    }
}

std::wstring CSongInfoHelper::GetPlaylistItemToolTip(const SongInfo& song_info, bool show_title, bool show_full_path)
{
    std::wstring str_tip;
    if (show_title)	
    {
        str_tip += GetDisplayStr(song_info, theApp.m_media_lib_setting_data.display_format);
        str_tip += _T("\r\n");
    }
    int song_index;
    if (show_full_path)
    {
        str_tip += CCommon::LoadText(IDS_PATH, _T(": "));
        str_tip += song_info.file_path.c_str();
    }
    else
    {
        str_tip += CCommon::LoadText(IDS_FILE_NAME, _T(": "));
        str_tip += song_info.GetFileName().c_str();
    }
    str_tip += _T("\r\n");

    str_tip += CCommon::LoadText(IDS_TITLE, _T(": "));
    str_tip += song_info.GetTitle().c_str();
    str_tip += _T("\r\n");

    str_tip += CCommon::LoadText(IDS_ARTIST, _T(": "));
    str_tip += song_info.GetArtist().c_str();
    str_tip += _T("\r\n");

    str_tip += CCommon::LoadText(IDS_ALBUM, _T(": "));
    str_tip += song_info.GetAlbum().c_str();
    str_tip += _T("\r\n");

    CString str_bitrate;
    str_bitrate.Format(CCommon::LoadText(IDS_BITRATE, _T(": %dkbps")), song_info.bitrate);
    str_tip += str_bitrate;
    return str_tip;
}
