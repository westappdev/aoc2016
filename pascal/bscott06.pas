{****************************************************************************
  Advent of Code 2016
  Day 6 (part 1 and 2)
****************************************************************************}

program bscott06;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes, SysUtils, CustApp
  { you can add units after this };

type

  { TAdventOfCodeDay06 }

  TAdventOfCodeDay06 = class(TCustomApplication)
  protected
    procedure DoRun; override;
  public
    constructor Create(TheOwner: TComponent); override;
    destructor Destroy; override;
  end;

{ TAdventOfCodeDay06 }

procedure TAdventOfCodeDay06.DoRun;
var
  CharCountArrArray: array [0..7, 'a'..'z'] of Integer;
  Password: array [0..7] of Char;
  CharCount, I : Integer;
  J: Char;
  CurrentLine: String;
  InputDataFile: text;
begin

  FillChar (CharCountArrArray,SizeOf(CharCountArrArray),0);
  FillChar (Password,SizeOf(Password),0);

  AssignFile(InputDataFile, 'day6_input.txt');
  Reset(InputDataFile);
  while not eof(InputDataFile) do
  begin
    readln(InputDataFile, CurrentLine);

    Inc(CharCountArrArray[0, CurrentLine[1]],1);
    Inc(CharCountArrArray[1, CurrentLine[2]],1);
    Inc(CharCountArrArray[2, CurrentLine[3]],1);
    Inc(CharCountArrArray[3, CurrentLine[4]],1);
    Inc(CharCountArrArray[4, CurrentLine[5]],1);
    Inc(CharCountArrArray[5, CurrentLine[6]],1);
    Inc(CharCountArrArray[6, CurrentLine[7]],1);
    Inc(CharCountArrArray[7, CurrentLine[8]],1);
  end;
  CloseFile(InputDataFile);

  for I := 0 to 7 do
  begin
       CharCount := 0;
       for J := 'a' to 'z' do
       begin
         if CharCount < CharCountArrArray[I, J] then
          begin
              Password[I] := J;
              CharCount := CharCountArrArray[I, J];
          end;
       end;
  end;

  writeln('Part A Password: ' + Password);

  FillChar (Password,SizeOf(Password),0) ;
  for I := 0 to 7 do
  begin
       CharCount := 0;
       for J := 'a' to 'z' do
       begin
         if (CharCountArrArray[I, J] > 0) and ((CharCount > CharCountArrArray[I, J]) or (CharCount = 0)) then
          begin
              Password[I] := J;
              CharCount := CharCountArrArray[I, J];
          end;
       end;
  end;
  writeln('Part B Password: ' + Password);

  { add your program here }
  ReadLn;

  // stop program loop
  Terminate;
end;

constructor TAdventOfCodeDay06.Create(TheOwner: TComponent);
begin
  inherited Create(TheOwner);
  StopOnException:=True;
end;

destructor TAdventOfCodeDay06.Destroy;
begin
  inherited Destroy;
end;

var
  Application: TAdventOfCodeDay06;
begin
  Application:=TAdventOfCodeDay06.Create(nil);
  Application.Title:='Advent of Code - Day 6';
  Application.Run;
  Application.Free;
end.

