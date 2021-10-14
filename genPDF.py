import pdfkit


def genPDF():

    # pdfkit.from_url('https://baidu.com', '/Users/yz/Desktop/out.pdf')
    pdfkit.from_file('ch1.html', 'out.pdf')
# pdfkit.from_string('Hello!', 'out.pdf')


if __name__ == '__main__':
    genPDF()
