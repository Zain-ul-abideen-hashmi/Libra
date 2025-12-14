import sys
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from PIL import Image, ImageDraw, ImageFont
import os

def send_email(user_email):
    # --- CONFIGURATION ---
    SENDER_EMAIL = "libra.project.admi@gmail.com"
    SENDER_PASSWORD = "kwcv iybf yisq gtub" # Use App Password, not real password

    # --- GENERATE IMAGE ---
    # Matte Black Background (20, 20, 20)
    img = Image.new('RGB', (600, 400), color=(20, 20, 20))
    d = ImageDraw.Draw(img)

    # Try to load a font, otherwise default
    try:
        # Windows usually has arial.ttf
        fnt_title = ImageFont.truetype("arial.ttf", 60)
        fnt_sub = ImageFont.truetype("arial.ttf", 30)
    except:
        fnt_title = ImageFont.load_default()
        fnt_sub = ImageFont.load_default()

    # Jade Green Color (0, 168, 107) -> Hex #00A86B
    jade_green = (0, 168, 107)

    # Draw Text centered
    d.text((300, 150), "LIBRA", font=fnt_title, fill=jade_green, anchor="mm")
    d.text((300, 220), "Thanks for Voting", font=fnt_sub, fill=jade_green, anchor="mm")

    img_path = "voter_card.png"
    img.save(img_path)

    # --- SEND EMAIL ---
    try:
        msg = MIMEMultipart()
        msg['Subject'] = "Your Libra Voting Card"
        msg['From'] = SENDER_EMAIL
        msg['To'] = user_email

        text = MIMEText("Thank you for participating in the election. Here is your commemorative card.", 'plain')
        msg.attach(text)

        with open(img_path, 'rb') as f:
            img_data = f.read()

        image = MIMEImage(img_data, name=os.path.basename(img_path))
        msg.attach(image)

        # Connect to Server
        s = smtplib.SMTP('smtp.gmail.com', 587)
        s.starttls()
        s.login(SENDER_EMAIL, SENDER_PASSWORD)
        s.sendmail(SENDER_EMAIL, user_email, msg.as_string())
        s.quit()
        print("Email Sent Successfully!")
    except Exception as e:
        print(f"Failed to send email: {e}")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        email_arg = sys.argv[1]
        send_email(email_arg)
    else:
        print("No email provided.")