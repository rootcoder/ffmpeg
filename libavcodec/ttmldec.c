 /*
 * TTML subtitle decoder
 * Copyright (c) 2023 Aidan Vaughan (TheDaChicken)
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <libxml/parser.h>
#include "avcodec.h"
#include "ass.h"
#include "ttmlenc.h"
#include "codec_internal.h"
#include "version.h"
#include "libavutil/bprint.h"
#include "libavutil/mem.h"
#include "libavutil/parseutils.h"
#include "stdio.h"

/**
 * @file
 * TTML subtitle decoder
 * @see https://www.w3.org/TR/ttml1/
 * @see https://www.w3.org/TR/ttml2/
 * @see https://www.w3.org/TR/ttml-imsc/rec
 */

static const char* TTML_HEADER =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<tt %s>%s</tt>";

typedef struct {
    const char* name;
    const char* fontfamily;
    uint8_t fontsize;
    uint8_t bold;
    uint8_t italic;
    int color;
    int backgroundColor;
    int alignment;
} TTMLStyle;

typedef struct {
    const char* style;
    const char* name;
} TTMLRegion;

typedef struct {
    xmlDocPtr doc;
    xmlNodePtr node;
    int readorder;
    TTMLStyle* styles;
    TTMLRegion* regions;
    uint32_t style_count;
    uint32_t region_count;
} TTMLContext;

const static TTMLStyle DEFAULT_STYLE = {
    "Default",
    ASS_DEFAULT_FONT, ASS_DEFAULT_FONT_SIZE,
    ASS_DEFAULT_BOLD, ASS_DEFAULT_ITALIC,
    ASS_DEFAULT_COLOR,
    ASS_DEFAULT_BACK_COLOR, ASS_DEFAULT_ALIGNMENT
};

static void init_style(TTMLStyle* style) {
    style->name = av_strdup("Default");
    style->fontfamily = av_strdup(ASS_DEFAULT_FONT);
    style->fontsize = ASS_DEFAULT_FONT_SIZE;
    style->bold = ASS_DEFAULT_BOLD;
    style->italic = ASS_DEFAULT_ITALIC;
    style->color = ASS_DEFAULT_COLOR;
    style->backgroundColor = ASS_DEFAULT_BACK_COLOR;
    style->alignment = ASS_DEFAULT_ALIGNMENT;
}

static av_cold int ttml_init(AVCodecContext *avctx)
{
    av_log(avctx, AV_LOG_ERROR, "ttml_init\n");
    return 0;
}

static int ttml_decode_frame(AVCodecContext *avctx, AVSubtitle *sub,
                             int *got_sub_ptr, const AVPacket *avpkt)
{
    TTMLContext *ttml = avctx->priv_data;
    int ret = 0;
    TTMLStyle* style;
    AVBPrint buf;
    xmlChar* default_str;
    xmlNodePtr p_node;

    ret = avpkt->size;

    av_log(avctx, AV_LOG_ERROR, "ttml_decode_frame %d\n", ret);

    return ret;
}

static av_cold int ttml_close(AVCodecContext *avctx)
{
    av_log(avctx, AV_LOG_ERROR, "ttml close\n");
    return 0;
}

const FFCodec ff_ttml_decoder = {
        .p.name         = "ttml",
        CODEC_LONG_NAME("TTML subtitle"),
        .priv_data_size = sizeof(TTMLContext),
        .p.type         = AVMEDIA_TYPE_SUBTITLE,
        .p.id           = AV_CODEC_ID_TTML,
        FF_CODEC_DECODE_SUB_CB(ttml_decode_frame),
        .init           = ttml_init,
        .flush          = ff_ass_decoder_flush,
        .close          = ttml_close,
};
