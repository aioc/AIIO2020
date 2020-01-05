from graphviz import Digraph
import sys

'''Coordinate system for diagrams that involve a number line
'''
class GridDiagram(object):
    def __init__(self, x_scale=1, y_scale=1):
        self.x_scale = x_scale
        self.y_scale = y_scale
        self.x_offset = 0
        self.y_offset = 0
        self.layer_to_y_scale = {}

    def getCoords(self, x, y):
        return (x*self.x_scale + self.x_offset,
                y*self.y_scale + self.y_offset)

    def setXOffset(self, x_offset):
        self.x_offset = x_offset

    def setYOffset(self, y_offset):
        self.y_offset = y_offset

    def renderGrid(self, cols, rows):
        for r in range(rows):
            for c in range(cols):
                n = Node()
                n.set('shape', 'square')
                n.set('width', self.x_scale)
                n.set('height', self.y_scale)
                n.set('pos', (c*self.y_scale, r*self.x_scale))
                n.render(g)

class Node(object):
    _nodes_id = 0
    def __init__(self):
        self.kwargs = {
            'name': 'id%d' % Node._nodes_id,
            'label': '', # Stop Graphviz from using the 'name' as the default label
        }
        Node._nodes_id += 1

    '''Sets a node attribute.
    
        Automatically converts between sensible python types for various attributes and
        the graphviz format.
    '''
    def set(self, attribute, value):
        # Do not set node name. Perhaps you meant label?
        assert(attribute != 'name')
        # Make sure that positions are fixed coordinates
        if attribute == 'pos':
            value = '{},{}!'.format(value[0], value[1])

        value = str(value)
        self.kwargs[attribute] = value
    
    def render(self, graph):
        graph.node(**self.kwargs)

def drawBot(g, i, j, c, label=''):
    x = (1, 0) if c in 'pb' else (-1, 0)
    y = (0, 1) if c in 'bd' else (0, -1)
    SC = 0.3
    for z in [x, y]:
        n = Node()
        n.set('shape', 'square')
        n.set('width', 0.2)
        n.set('height', 0.2)
        n.set('pos', grid.getCoords(i+z[0]*SC, j+z[1]*SC))
        n.render(g)

    n = Node()
    n.set('shape', 'circle')
    n.set('label', label)
    n.set('fillcolor', 'white')
    n.set('linecolor', 'black')
    n.set('style', 'filled')
    n.set('fixedsize', True)
    n.set('pos', grid.getCoords(i, j))
    n.render(g)

def drawBots(g, bots, facing):
    for r, l in enumerate(bots):
        for c, b in enumerate(l):
            # Swap r and c since drawBot() is written in terms of x and y
            drawBot(g, c, len(bots)-r-1, facing[r][c], b)


grid = GridDiagram(0.75, 0.75)

g = Digraph(format='svg', engine='neato')
# g = Digraph(format='svg', engine='neato', body=["graph [ dpi = 300 ];"])
drawBot(g, 0, 0, 'p')
drawBot(g, 1, 0, 'q')
drawBot(g, 2, 0, 'b')
drawBot(g, 3, 0, 'd')
g.render('fourbots')

g = Digraph(format='svg', engine='neato')
grid.renderGrid(7, 1)
drawBots(g,
[
    [15, -5, 100, -40, 10, 10, 10]
],[
    ['b', 'p', 'q', 'b', 'd', 'p', 'q']
])
g.render('sample1')

g = Digraph(format='svg', engine='neato')
grid.renderGrid(2, 2)
drawBots(g,
[
    [100, 100],
    [100, 100],
],[
    ['p', 'q'],
    ['b', 'd'],
])
g.render('sample2')

g = Digraph(format='svg', engine='neato')
grid.renderGrid(3, 3)
drawBots(g,
[
    [-10, 4, -10],
    [3, 1, -10],
    [6, 2, 8]
],[
    ['p', 'q', 'd'],
    ['p', 'd', 'd'],
    ['b', 'b', 'q'],
])
g.render('sample3')
