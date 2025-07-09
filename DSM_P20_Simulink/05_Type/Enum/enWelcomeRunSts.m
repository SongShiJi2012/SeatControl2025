%% Create enWelcomeRunSts enum

classdef enWelcomeRunSts < Simulink.IntEnumType

    enumeration
        EN_Wel_NULL(0)
        EN_Wel_BWMoveSuccess(1)
        EN_Wel_FWMoveSuccess(2)
        EN_Wel_BWMoveFail(3)
        EN_Wel_FWMoveFail(4)
        EN_Wel_FWBreakBW(5)
        EN_Wel_BWBreakFW(6)
        EN_Wel_BWOngoing(7)
        EN_Wel_FWOngoing(8)
        EN_Wel_Exit(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enWelcomeRunSts.EN_Wel_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '迎宾功能座椅状态&#10;0x00: enNull 默认初始化状态&#10;0x01: enBWMoveSuccess 后移成功&#10;0x02: enFWMoveSuccess 前移成功&#10;0x03: enBWMoveFail 后移失败&#10;0x04: enFWMoveFail 前移失败&#10;0x05: enFWBreakBW 后移过程中执行前移&#10;0x06: enBWBreakFW 前移过程中执行后移&#10;0x07: enBWOngoing 后移过程中&#10;0x08: enFWOngoing 前移过程中&#10;0x09: enExit 退出迎宾功能,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
