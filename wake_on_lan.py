#! python3

"""
#wake_on_lan.py
'Wake On Lan' (WOL) Script
Utilizamos la librería 'binascii' para convertir la dirección MAC
a bytes. Este paso no es estrictamente necesario porque el usuario podría escribir
la dirección MAC en bytes, pero lo hace más 'amigable'
Más información en el link debajo.
The Nerdy Apprentice
(https://thenerdyapprentice.blogspot.com)
"""

import socket
import binascii

pc = '7d:82:55:a4:ef:90' # Dirección MAC de la PC que queremos 'despertar'

# Convertimos la direccion MAC a bytes para ser pasados a la función
address = binascii.unhexlify(pc.replace(':', ''))  

def wol(macAdress):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    wolPack = b'\xff' * 6 + macAdress * 16 # Armamos el 'paquete mágico' a enviar
    print('Enviando paquete WOL: %s' % wolPack)
    s.sendto(wolPack, ('<broadcast>', 7)) # Enviamos el paquete.
    print('Paquete enviado.')
    
wol(address) # Llamamos a la función y le pasamos la dirección MAC

