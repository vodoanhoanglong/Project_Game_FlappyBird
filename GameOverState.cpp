#include <sstream>
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"
#include "GameState.hpp"

#include <iostream>
#include <fstream>

namespace BTL
{
    GameOverState::GameOverState(GameDataRef data, int score) : _data(data), _score(score) // ds khởi tạo gán _data = data, _score = score
    {
        
    }
    
    void GameOverState::Init()
    {
        std::ifstream readFile; // khai báo readFile để đọc file
        readFile.open( "Resources/Highscore.txt" ); // mở file lên
        
        if ( readFile.is_open( ) ) // trả về true nếu 1 tệp đang mở và đc liên kết với nguồn này
        {
            while ( !readFile.eof( ) ) // nếu hết file thì trả về true -> true == false -> dừng lặp
            {
                readFile >> _highScore; // đưa ký tự vào _highScore
            }
        }
        
        readFile.close( ); // đóng file
        
        std::ofstream writeFile( "Resources/Highscore.txt" ); // khai báo writeFile để ghi file
        
        if ( writeFile.is_open( ) ) // trả về true nếu 1 tệp đang mở và đc liên kết với nguồn này
        {
            if ( _score > _highScore ) // nếu _score hiện tại > _highScore trong thì tiếp
            {
                _highScore = _score; // gán lại _highScore = _score
            }
            
            writeFile << _highScore; // xuất _highScore ra file 
        }
        
        writeFile.close( ); // đóng
        
        this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH); // gọi hàm LoadTexture trong AssetsManager.cpp gồm tên tự định nghĩa và 1 hằng số là tên chứa đường dẫn file 
        this->_data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH); // tương tự
        this->_data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
        this->_data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
        this->_data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);
        
        _background.setTexture(this->_data->assets.GetTexture("Game Over Background")); // setTexture đặt _background có kết cấu mới = gọi hàm GetTexture trong AssetManager.cpp để lấy hình ra
        _gameOverTitle.setTexture(this->_data->assets.GetTexture("Game Over Title")); // tương tự
        _gameOverContainer.setTexture(this->_data->assets.GetTexture("Game Over Body"));
        _retryButton.setTexture(this->_data->assets.GetTexture("Play Button"));
        
        _gameOverContainer.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_gameOverContainer.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (_gameOverContainer.getGlobalBounds().height / 2)));
        // đặt vị trí của _gameOverContainer(sf::Vector2f là vector chứa 2 kiểu dữ liệu float((kích thước ngang cửa sổ / 2) - (chiều rộng max của kết cấu _gameOverContainer / 2), (kích thước dọc cửa sổ / 2) - (chiều cao max của _gameOverContainer / 2)))
        _gameOverTitle.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_gameOverTitle.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y - (_gameOverTitle.getGlobalBounds().height * 1.2)));
        // tương tự
        _retryButton.setPosition(sf::Vector2f((_data->window.getSize().x / 2) - (_retryButton.getGlobalBounds().width / 2), _gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height + (_retryButton.getGlobalBounds().height * 0.2)));
        
        _scoreText.setFont(this->_data->assets.GetFont("Flappy Font")); // setFont là đặt font chữ theo hàm GetFont trong AssesManager.cpp
        _scoreText.setString(std::to_string(_score)); // cập nhật ký tự cũ thành ký tự mới thông qua biến _score
        _scoreText.setCharacterSize(56); // đặt kích thước ký tự là 56
        _scoreText.setFillColor(sf::Color::White); // đặt màu cho ký tự là màu trắng
        _scoreText.setOrigin(sf::Vector2f(_scoreText.getGlobalBounds().width / 2, _scoreText.getGlobalBounds().height / 2)); // setOrigin thiết lập nguồn gốc cục bộ của đối tượng
		// Vector2f là 1 vector có chứa 2 dữ liệu kiểu float(max width của _scoreText / 2, max height _scoreText / 2)
        _scoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 2.15)); // setPosition là đặt vị trí cho đối tượng
		// Vector2f là 1 vector có chứa 2 dữ liệu kiểu float(kích thước ngang của cửa sổ / 10 * 7.25, kích thước dọc của cửa sổ / 2.15)
        
        _highScoreText.setFont(this->_data->assets.GetFont("Flappy Font")); // tương tự dòng 64 trở xuống dòng 70
        _highScoreText.setString(std::to_string(_highScore));
        _highScoreText.setCharacterSize(56);
        _highScoreText.setFillColor(sf::Color::White);
        _highScoreText.setOrigin(sf::Vector2f(_highScoreText.getGlobalBounds().width / 2, _highScoreText.getGlobalBounds().height / 2));
        _highScoreText.setPosition(sf::Vector2f(_data->window.getSize().x / 10 * 7.25, _data->window.getSize().y / 1.78));
        
        if ( _score >= PLATINUM_MEDAL_SCORE ) // nếu _score >= 100
        {
            _medal.setTexture( _data->assets.GetTexture( "Platinum Medal" ) ); // setTexture đặt _medal có kết cấu mới = gọi hàm GetTexture trong AssetManager.cpp để lấy hình ra
        }
        else if ( _score >= GOLD_MEDAL_SCORE ) // nếu >= 25
        {
            _medal.setTexture( _data->assets.GetTexture( "Gold Medal" ) ); // tương tự dòng 82
        }
        else if ( _score >= SILVER_MEDAL_SCORE ) // nếu >= 5
        {
            _medal.setTexture( _data->assets.GetTexture( "Silver Medal" ) );
        }
        else // ngược lại hết mấy cái trên
        {
            _medal.setTexture( _data->assets.GetTexture( "Bronze Medal" ) );
        }
        
        _medal.setPosition( 175, 465 ); // đặt vị trí của _medal là x: 175, y: 465
    }
    
    void GameOverState::HandleInput()
    {
        sf::Event event; // khai báo biến sự kiện
        
        while (this->_data->window.pollEvent(event)) // nhiều sự kiện có thể trong hàng đợi sự kiện nên khai báo vòng lặp để xử lý mọi sự kiện
        {
            if (sf::Event::Closed == event.type) // nếu sự kiện đóng cửa sổ = loại sự kiện đó trong EventType
            {
                this->_data->window.close(); // đóng cửa sổ
            }
            
            if (this->_data->input.IsSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window)) // gọi đến hàm IsSpriteClicked nếu click trong khung _retryButton bằng chuột trái thì true
            {
                this->_data->machine.AddState(StateRef(new GameState(_data)), true); // gọi hàm AddState trong đối tượng machine của lớp StateMachine
			    // sau đó gọi hàm khởi tạo của class StateRef, new GameState ở đây là khi gọi hàm sẽ truyền vào 1 đối tượng và sẽ cấp phát bộ nhớ cho nó theo kiểu dữ liệu GameState có _data ô nhớ
            }
        }
    }
    
    void GameOverState::Update(float dt)
    {
        
    }
    
    void GameOverState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red); // xóa toàn bộ màu đỏ trên cửa sổ
        
        this->_data->window.draw(this->_background); // vẽ this->_background lên cửa sổ
        
        _data->window.draw(_gameOverTitle); // tương tự
        _data->window.draw(_gameOverContainer);
        _data->window.draw(_retryButton);
        _data->window.draw(_scoreText);
        _data->window.draw(_highScoreText);
        
        _data->window.draw( _medal );
        
        this->_data->window.display(); // hiển thị trên màn hình những gì đã được hiển thị trong cửa sổ cho đến nay.
    }
}
