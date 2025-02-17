from flask import Flask, request
import datetime

app = Flask(__name__)

@app.route('/guardar-codigo', methods=['POST'])
def guardar_codigo():
    data = request.get_json()
    if not data or 'codigo' not in data:
        return {'error': 'Nenhum código fornecido'}, 400
    
    codigo = data['codigo']
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    try:
        with open('ir_codigos.txt', 'a') as file:
            file.write(f"{timestamp}: {codigo}\n")
        return {'message': 'Código armazenado com sucesso'}, 200
    except Exception as e:
        return {'error': f'Erro ao salvar o código: {str(e)}'}, 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)