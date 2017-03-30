#ifndef _BOOK_MAKER_H_
#define _BOOK_MAKER_H_
#include "utility.h"
#include <fstream>
#include <stdexcept>
#include <exception>

struct StringChapter {
    string name;
    vector<string> lines;
};

struct PublishedBook {
    string name;
    string owner;
    vector<string> authors;
    vector <StringChapter> chapters;
};

class BookMaker {
public:
    static void makeHtmlFile(PublishedBook& book , string fileAddress);
    static void makeCssFile();
    static void makeJsFile();
private:
};

void BookMaker::makeHtmlFile( PublishedBook& book, string fileAddress ) {
//    Utility::makeFolder("Library");

//    if( !Utility::fileExist("./Library/style.css") )
//        makeCssFile();

//    if( !Utility::fileExist("./Library/javascript.js") )
//        makeJsFile();

    // make new file and open file
    ofstream html;
    string fileName = fileAddress;
    html.open( fileName.c_str() );
    if( !html )
        throw std::invalid_argument( "can't open html file" );

    html << "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF-8\"> <link rel=\"stylesheet\" href=\"style.css\"> <title>" << endl;
    html << book.name << endl;
    html << "</title> <script src=\"jquery.min.js\"></script> <script src=\"javascript.js\"></script> </head> <body> <div class=\"blueBack\"> <div class=\"cont\"> <div class=\"header\"> <div class=\"title\">" << endl;
    html << book.name << endl;
    html << "</div> <div class=\"authors\">" << endl;

    for (size_t i = 0; i < book.authors.size(); i++) {
        html << "<div class=\"author\">" << book.authors[i] << "</div>" << endl;
    }

    html << "</div> </div> <div class=\"cont-under\"> <div class=\"sidebar\">" << endl;

    for (size_t i = 0; i < book.chapters.size(); i++) {
        html << "<li id=\"" << i << "\" class=\"list\">" << book.chapters[i].name << "</li>" << endl;
    }

    html << "</div> <div class=\"paper\">" << endl;

    for (size_t i = 0; i < book.chapters.size(); i++) {
        html << "<div id =\"t" << i << "\" class=\"sec\">" << endl;
        html << "<h1>" << book.chapters[i].name << "</h1>" << endl;
        html << "<div class=\"text\">" << endl;

        for (size_t j = 0; j < book.chapters[i].lines.size(); j++) {
            html << "<span>" << book.chapters[i].lines[j] << "</span>" << endl;
        }

        html << "</div></div>" << endl;
    }

    html << "</div> </div> </div> </div> </div> </body> </html>" << endl;
}

void BookMaker::makeCssFile() {
    string css = "html,body,div,span,applet,object,iframe,h1,h2,h3,h4,h5,h6,p,blockquote,pre,a,abbr,acronym,address,big,cite,code,del,dfn,em,img,ins,kbd,q,s,samp,small,strike,strong,sub,sup,tt,var,b,u,i,center,dl,dt,dd,ol,ul,li,fieldset,form,label,legend,table,caption,tbody,tfoot,thead,tr,th,td,article,aside,canvas,details,embed,figure,figcaption,footer,header,hgroup,menu,nav,output,ruby,section,summary,time,mark,audio,video{margin:0;padding:0;border:0;font-size:100%;font:inherit;vertical-align:baseline}article,aside,details,figcaption,figure,footer,header,hgroup,menu,nav,section{display:block}body{line-height:1}ol,ul{list-style:none}blockquote,q{quotes:none}blockquote:before,blockquote:after,q:before,q:after{content:'';content:none}table{border-collapse:collapse;border-spacing:0}.blueBack{width:100%;height:400px;background-color:#4285f4;float:left}.cont{width:1000px;height:900px;margin:0 auto;margin-top:50px}.header{width:100%}.title{font-family:Arial;font-size:24px;color:#fff}.owner{color:#fff;font-family:arial;font-size:12px;margin-left:1px;margin-top:3px}.authors{margin-left:1px;margin-top:3px}.author{font-size:10px;color:#fff;font-family:arial;float:left;margin-left:13px;opacity:.7}.author:first-child{margin-left:0}.list{font-family:arial;color:#fff;font-size:15px;cursor:pointer;padding:10px;padding-left:10px;list-style:none;opacity:.8;transition:all .4s;transition:border 0s;background-color:#4285f4}.list:hover{background-color:#3b78e7;opacity:1}.list-selected{font-weight:700;padding-left:8px;border-left:2px solid #fff;opacity:1}.sidebar{width:300px;margin-top:50px;clear:left;float:left}.paper{background-color:#fff;width:700px;float:left;margin-top:50px;box-shadow:0 0 6px 0 rgba(0,0,0,.46);padding-bottom:130px}h1{font-family:Times,serif;font-size:40px;margin-top:80px;padding-left:80px;padding-bottom:30px;clear:both}span{clear: both;float:left;font-family:Times,serif}.text{position:relative;padding-left:80px;padding-right:80px}.hidden{display:none}.sec{width:700px;float:left} ";
    Utility::makeFolder("Library");

    // make new file and open file
    ofstream file;
    file.open( "./Library/style.css" );

    file << css;
}
void BookMaker::makeJsFile() {
    string js = "$(document).ready(function(){$('.sec').addClass('hidden'),$('#0').addClass('list-selected'),$('#t0').removeClass('hidden'),a=0,$('.list').click(function(){$('#t1').addClass('hidden'),$('#t'+a).addClass('hidden'),$('.list').removeClass('list-selected'),$(this).addClass('list-selected'),a=$(this).attr('id'),$('#t'+a).removeClass('hidden')})});";
    Utility::makeFolder("Library");

    // make new file and open file
    ofstream file;
    file.open( "./Library/javascript.js" );

    file << js;
}



#endif /* _BOOK_MAKER_H_ */
