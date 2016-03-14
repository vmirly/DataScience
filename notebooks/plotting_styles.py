import matplotlib as mpl



def set_lightblueBGcolor():
    """ To set the default plotting style
        background color: light-blue
        grid: dashed line, orange color
    """
    style = {'axes.axisbelow': True,
             'axes.facecolor': '#DADAF4',
             'axes.grid': True,
             'font.family': 'Arial',
             'grid.color': 'orange',
             'grid.linestyle': '--',
             'grid.linewidth': 1,
             'image.cmap': 'Greys',
             'legend.frameon': False,
             'legend.numpoints': 3,
             'legend.scatterpoints': 1,
             'lines.solid_capstyle': 'round',
             'pdf.fonttype': 42,
             'text.color': '.15',
             'xtick.color': '.15',
             'xtick.direction': 'out',
             'xtick.major.size': 0,
             'xtick.minor.size': 0,
             'ytick.color': '.15',
             'ytick.direction': 'out',
             'ytick.major.size': 0,
             'ytick.minor.size': 0}
    mpl.rcParams.update(style)
