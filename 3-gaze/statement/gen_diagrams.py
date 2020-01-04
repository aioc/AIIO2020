from graphviz import Digraph
import sys

'''Coordinate system for diagrams that involve a number line
'''
class LineDiagram(object):
    def __init__(self, x_scale=1, y_scale=1):
        self.x_scale = x_scale
        self.y_scale = y_scale
        self.x_offset = 0
        self.y_offset = 0
        self.layer_to_y_scale = {}

    def addLayer(self, layer_name, y_scale):
        self.layer_to_y_scale[layer_name] = y_scale

    def getCoords(self, x, layer):
        return (x*self.x_scale + self.x_offset,
                self.layer_to_y_scale[layer]*self.y_scale + self.y_offset)

    def setXOffset(self, x_offset):
        self.x_offset = x_offset

    def setYOffset(self, y_offset):
        self.y_offset = y_offset


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


def drawCase(g, quota, facing, flowers, rip=[]):
    g.node_attr['fontname'] = 'helvetica'
    g.node_attr['fontsize'] = '20'
    for i, (q, f, fl) in enumerate(zip(quota, facing, flowers)):
        if i+1 in rip:
            continue
        n = Node()
        n.set('shape', 'square')
        n.set('label', '←' if f == 'L' else '→')
        n.set('pos', line.getCoords(i, 'statues'))
        n.render(g)

        n = Node()
        n.set('shape', 'none')
        n.set('label', q)
        n.set('pos', line.getCoords(i, 'quota'))
        n.render(g)

        for j in range(fl):
            n = Node()
            n.set('shape', 'none')
            n.set('label', '✿')
            n.set('pos', line.getCoords(i, 'flower' + str(j)))
            n.render(g)


line = LineDiagram(y_scale = 0.6)
line.addLayer('statues', 0)
line.addLayer('quota', -1)
for i in range(10):
    line.addLayer('flower' + str(i), 0.6 + i*0.4)


g = Digraph(format='svg', engine='neato')
drawCase(g, [2, 3, 6, 1, 2, 3], 'RRLLRL', [3, 3, 0, 0, 2, 0])
line.setYOffset(-2.6)
drawCase(g, [2, 3, 6, 1, 2, 3], 'RRLLRL', [1, 0, 5, 0, 0, 0], [5])
line.setYOffset(-4.5)
drawCase(g, [2, 3, 6, 1, 2, 3], 'RRLLRL', [0, 2, 0, 1, 0, 0], [5, 3])
g.render('sample2')

line.setYOffset(0)
g = Digraph(format='svg', engine='neato')
drawCase(g, [5, 1, 2, 1], 'RRLR', [3, 0, 1, 1])
g.render('sample1')
