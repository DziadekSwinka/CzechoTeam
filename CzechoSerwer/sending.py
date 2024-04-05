import smtplib
import sys

if __name__ == "__main__":
    email = "jakub.kleczek.72@gmail.com"
    email_receiver = "czechoteam2005@gmail.com"
    text = "Alarm!\nWykryto nieprawidlowosc w dzialaniu maszyny \nKordynaty zdarzenia:" + str(sys.argv[1])+" "+str(sys.argv[2])

    try:
        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login(email, "iijhyuixgffabgxp")
        server.sendmail(email, email_receiver, text)
        print("E-mail został wysłany.")
    except Exception as e:
        print("Wystąpił błąd podczas wysyłania e-maila:", str(e))
    finally:
        if 'server' in locals():
            server.quit()
