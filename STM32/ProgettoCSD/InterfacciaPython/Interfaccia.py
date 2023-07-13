import serial
import time
import matplotlib.pyplot as plt

ser=serial.Serial(port='COM7',baudrate=9600) 

if not ser.isOpen():
    ser.open()
    
x_data = []
y_temp = []
y_umid = []
y_intens = []
y_temp_2 = []
y_umid_2 = []
y_intens_2 = []

#grafico 1

plt.ion()  # Abilita la modalità interattiva
fig, axs = plt.subplots(3, 2)  # Create the figure and two subplots

ax   =  axs[0,0]
ax_2 =  axs[1,0]
ax1_intens = axs[2,0]
ax_3 =  axs[0,1]
ax_4 =  axs[1,1]
ax2_intens = axs[2,1]


line, = ax.plot(x_data, y_temp, color="red")  # Crea la linea del grafico
ax.grid(True)
ax.set_xlabel('Campioni')
ax.set_ylabel('Temperatura')
ax.set_title('Canale 1')

#grafico 2

line_2, = ax_2.plot(x_data, y_umid, color="blue")  # Crea la linea del grafico
ax_2.grid(True)
ax_2.set_xlabel('Campioni')
ax_2.set_ylabel('Umidità')

#grafico 1_intens

line1_intens, = ax1_intens.plot(x_data, y_umid, color="green")  # Crea la linea del grafico
ax1_intens.grid(True)
ax1_intens.set_xlabel('Campioni')
ax1_intens.set_ylabel('Intensità')

#grafico 3

line_3, = ax_3.plot(x_data, y_temp, color="red")  # Crea la linea del grafico
ax_3.grid(True)
ax_3.set_xlabel('Campioni')
ax_3.set_ylabel('Temperatura')
ax_3.set_title('Canale 2')

#grafico 4

line_4, = ax_4.plot(x_data, y_umid, color="blue")  # Crea la linea del grafico
ax_4.grid(True)
ax_4.set_xlabel('Campioni')
ax_4.set_ylabel('Umidità')

#grafico 2_intens

line2_intens, = ax2_intens.plot(x_data, y_umid, color="green")  # Crea la linea del grafico
ax2_intens.grid(True)
ax2_intens.set_xlabel('Campioni')
ax2_intens.set_ylabel('Intensità')



nuovo_x = 0
nuovo_y_temp = 0
nuovo_y_umid = 0
nuovo_y_intens = 0

nuovo_y_temp_2 = 0
nuovo_y_umid_2 = 0
nuovo_y_intens_2 = 0

while True:
    time.sleep(10)
    s=ser.readline().decode().rstrip()  # Legge una linea dalla porta seriale e rimuove i caratteri di fine riga
    temp = s.split('\n')
    data = temp[0].split('+')
    #print (s)
    
    Temp_y_temp = float(data[0])
    Temp_y_umid = float(data[1])
    Temp_intensita = float(data[2])
    
    print("Sensore 1")
    print("temperatura: "+str(Temp_y_temp))
    print("umidità: "+str(Temp_y_umid))
    print("Intensita: "+str(Temp_intensita)+"\n\n")
    
    s_2=ser.readline().decode().rstrip()  # Legge una linea dalla porta seriale e rimuove i caratteri di fine riga
    temp_2 = s_2.split('\n')
    data_2 = temp_2[0].split('+')
    #print (s)
    
    Temp_y_temp_2 = float(data_2[0])
    Temp_y_umid_2 = float(data_2[1])
    Temp_intensita_2 = float(data_2[2])
    
    print("Sensore 2")
    print("temperatura: "+str(Temp_y_temp_2))
    print("umidità: "+str(Temp_y_umid_2))
    print("Intensita: "+str(Temp_intensita_2)+"\n\n")
    
    #Temp_x = float(24.3) + nuovo_x
    #Temp_y = float(50) + nuovo_y
    
    nuovo_y_temp = Temp_y_temp
    nuovo_y_umid = Temp_y_umid
    nuovo_y_intens = Temp_intensita
    
    y_temp.append(nuovo_y_temp)
    y_umid.append(nuovo_y_umid)
    y_intens.append(nuovo_y_intens)
    
    nuovo_y_temp_2 = Temp_y_temp_2
    nuovo_y_umid_2 = Temp_y_umid_2
    nuovo_y_intens_2 = Temp_intensita_2
    
    y_temp_2.append(nuovo_y_temp_2)
    y_umid_2.append(nuovo_y_umid_2)
    y_intens_2.append(nuovo_y_intens_2)
    
    nuovo_x = nuovo_x + 1
    
    x_data.append(nuovo_x)
    
    # Aggiorna il grafico 1
    line.set_data(x_data, y_temp)
    ax.relim()  # Aggiorna i limiti degli assi
    ax.autoscale_view()  # Riscalatura automatica degli assi
    
    # Aggiorna il grafico 2
    line_2.set_data(x_data, y_umid)
    ax_2.relim()  # Aggiorna i limiti degli assi
    ax_2.autoscale_view()  # Riscalatura automatica degli assi
    
    # Aggiorna il grafico 1_intens
    line1_intens.set_data(x_data, y_intens)
    ax1_intens.relim()  # Aggiorna i limiti degli assi
    ax1_intens.autoscale_view()  # Riscalatura automatica degli assi
    
    # Aggiorna il grafico 3
    line_3.set_data(x_data, y_temp_2)
    ax_3.relim()  # Aggiorna i limiti degli assi
    ax_3.autoscale_view()  # Riscalatura automatica degli assi
    
    # Aggiorna il grafico 4
    line_4.set_data(x_data, y_umid_2)
    ax_4.relim()  # Aggiorna i limiti degli assi
    ax_4.autoscale_view()  # Riscalatura automatica degli assi
    
    # Aggiorna il grafico 1_intens
    line2_intens.set_data(x_data, y_intens_2)
    ax2_intens.relim()  # Aggiorna i limiti degli assi
    ax2_intens.autoscale_view()  # Riscalatura automatica degli assi
    
    fig.canvas.draw()
    fig.canvas.flush_events()
    
    plt.pause(0.01)  # Pausa per l'aggiornamento del grafico
    
    
plt.ioff()  # Disabilita la modalità interattiva
plt.show()  # Mostra il grafico
ser.close()