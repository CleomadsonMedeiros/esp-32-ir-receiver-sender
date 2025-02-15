from flask import Flask, request
import datetime

app = Flask(__name__)

@app.route('/store-code', methods=['POST'])
def store_code():
    data = request.get_json()
    if not data or 'code' not in data:
        return {'error': 'Nenhum código fornecido'}, 400
    
    code = data['code']
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    try:
        with open('ir_codes.txt', 'a') as file:
            file.write(f"{timestamp}: {code}\n")
        return {'message': 'Código armazenado com sucesso'}, 200
    except Exception as e:
        return {'error': f'Erro ao salvar o código: {str(e)}'}, 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)